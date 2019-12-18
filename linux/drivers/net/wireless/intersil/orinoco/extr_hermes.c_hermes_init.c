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
typedef  int u16 ;
struct hermes {int inten; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int CMD_BUSY_TIMEOUT ; 
 int ENODEV ; 
 int /*<<< orphan*/  EVACK ; 
 int /*<<< orphan*/  EVSTAT ; 
 int HERMES_CMD_BUSY ; 
 int /*<<< orphan*/  HERMES_CMD_INIT ; 
 int /*<<< orphan*/  INTEN ; 
 int hermes_doicmd_wait (struct hermes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hermes_read_regn (struct hermes*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hermes_write_regn (struct hermes*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int hermes_init(struct hermes *hw)
{
	u16 reg;
	int err = 0;
	int k;

	/* We don't want to be interrupted while resetting the chipset */
	hw->inten = 0x0;
	hermes_write_regn(hw, INTEN, 0);
	hermes_write_regn(hw, EVACK, 0xffff);

	/* Normally it's a "can't happen" for the command register to
	   be busy when we go to issue a command because we are
	   serializing all commands.  However we want to have some
	   chance of resetting the card even if it gets into a stupid
	   state, so we actually wait to see if the command register
	   will unbusy itself here. */
	k = CMD_BUSY_TIMEOUT;
	reg = hermes_read_regn(hw, CMD);
	while (k && (reg & HERMES_CMD_BUSY)) {
		if (reg == 0xffff) /* Special case - the card has probably been
				      removed, so don't wait for the timeout */
			return -ENODEV;

		k--;
		udelay(1);
		reg = hermes_read_regn(hw, CMD);
	}

	/* No need to explicitly handle the timeout - if we've timed
	   out hermes_issue_cmd() will probably return -EBUSY below */

	/* According to the documentation, EVSTAT may contain
	   obsolete event occurrence information.  We have to acknowledge
	   it by writing EVACK. */
	reg = hermes_read_regn(hw, EVSTAT);
	hermes_write_regn(hw, EVACK, reg);

	/* We don't use hermes_docmd_wait here, because the reset wipes
	   the magic constant in SWSUPPORT0 away, and it gets confused */
	err = hermes_doicmd_wait(hw, HERMES_CMD_INIT, 0, 0, 0, NULL);

	return err;
}