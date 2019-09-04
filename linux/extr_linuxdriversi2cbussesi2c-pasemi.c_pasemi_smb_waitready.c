#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pasemi_smbus {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int ETIME ; 
 int /*<<< orphan*/  REG_SMSTA ; 
 unsigned int SMSTA_MTN ; 
 unsigned int SMSTA_XEN ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 unsigned int reg_read (struct pasemi_smbus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct pasemi_smbus*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int pasemi_smb_waitready(struct pasemi_smbus *smbus)
{
	int timeout = 10;
	unsigned int status;

	status = reg_read(smbus, REG_SMSTA);

	while (!(status & SMSTA_XEN) && timeout--) {
		msleep(1);
		status = reg_read(smbus, REG_SMSTA);
	}

	/* Got NACK? */
	if (status & SMSTA_MTN)
		return -ENXIO;

	if (timeout < 0) {
		dev_warn(&smbus->dev->dev, "Timeout, status 0x%08x\n", status);
		reg_write(smbus, REG_SMSTA, status);
		return -ETIME;
	}

	/* Clear XEN */
	reg_write(smbus, REG_SMSTA, SMSTA_XEN);

	return 0;
}