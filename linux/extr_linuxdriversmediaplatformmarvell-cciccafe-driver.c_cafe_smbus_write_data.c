#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  unsigned int u8 ;
typedef  unsigned int u16 ;
struct mcam_camera {int /*<<< orphan*/  dev_lock; } ;
struct cafe_camera {int /*<<< orphan*/  smbus_wait; struct mcam_camera mcam; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAFE_SMBUS_TIMEOUT ; 
 int EIO ; 
 int /*<<< orphan*/  REG_TWSIC0 ; 
 int /*<<< orphan*/  REG_TWSIC1 ; 
 unsigned int TWSIC0_CLKDIV ; 
 unsigned int TWSIC0_EN ; 
 unsigned int TWSIC0_OVMAGIC ; 
 unsigned int TWSIC0_SID ; 
 unsigned int TWSIC0_SID_SHIFT ; 
 unsigned int TWSIC1_ADDR ; 
 unsigned int TWSIC1_ADDR_SHIFT ; 
 unsigned int TWSIC1_ERROR ; 
 unsigned int TWSIC1_WSTAT ; 
 int /*<<< orphan*/  cafe_smbus_write_done (struct mcam_camera*) ; 
 int /*<<< orphan*/  cam_err (struct cafe_camera*,char*,unsigned int,unsigned int,unsigned int) ; 
 unsigned int mcam_reg_read (struct mcam_camera*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcam_reg_write (struct mcam_camera*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cafe_smbus_write_data(struct cafe_camera *cam,
		u16 addr, u8 command, u8 value)
{
	unsigned int rval;
	unsigned long flags;
	struct mcam_camera *mcam = &cam->mcam;

	spin_lock_irqsave(&mcam->dev_lock, flags);
	rval = TWSIC0_EN | ((addr << TWSIC0_SID_SHIFT) & TWSIC0_SID);
	rval |= TWSIC0_OVMAGIC;  /* Make OV sensors work */
	/*
	 * Marvell sez set clkdiv to all 1's for now.
	 */
	rval |= TWSIC0_CLKDIV;
	mcam_reg_write(mcam, REG_TWSIC0, rval);
	(void) mcam_reg_read(mcam, REG_TWSIC1); /* force write */
	rval = value | ((command << TWSIC1_ADDR_SHIFT) & TWSIC1_ADDR);
	mcam_reg_write(mcam, REG_TWSIC1, rval);
	spin_unlock_irqrestore(&mcam->dev_lock, flags);

	/* Unfortunately, reading TWSIC1 too soon after sending a command
	 * causes the device to die.
	 * Use a busy-wait because we often send a large quantity of small
	 * commands at-once; using msleep() would cause a lot of context
	 * switches which take longer than 2ms, resulting in a noticeable
	 * boot-time and capture-start delays.
	 */
	mdelay(2);

	/*
	 * Another sad fact is that sometimes, commands silently complete but
	 * cafe_smbus_write_done() never becomes aware of this.
	 * This happens at random and appears to possible occur with any
	 * command.
	 * We don't understand why this is. We work around this issue
	 * with the timeout in the wait below, assuming that all commands
	 * complete within the timeout.
	 */
	wait_event_timeout(cam->smbus_wait, cafe_smbus_write_done(mcam),
			CAFE_SMBUS_TIMEOUT);

	spin_lock_irqsave(&mcam->dev_lock, flags);
	rval = mcam_reg_read(mcam, REG_TWSIC1);
	spin_unlock_irqrestore(&mcam->dev_lock, flags);

	if (rval & TWSIC1_WSTAT) {
		cam_err(cam, "SMBUS write (%02x/%02x/%02x) timed out\n", addr,
				command, value);
		return -EIO;
	}
	if (rval & TWSIC1_ERROR) {
		cam_err(cam, "SMBUS write (%02x/%02x/%02x) error\n", addr,
				command, value);
		return -EIO;
	}
	return 0;
}