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
struct fdomain {scalar_t__ base; } ;
struct Scsi_Host {int this_id; } ;

/* Variables and functions */
 int BCTL_BUSEN ; 
 int BCTL_SEL ; 
 int BIT (int) ; 
 int BSTAT_BSY ; 
 int PARITY_MASK ; 
 scalar_t__ REG_ACTL ; 
 scalar_t__ REG_BCTL ; 
 scalar_t__ REG_BSTAT ; 
 scalar_t__ REG_SCSI_DATA_NOACK ; 
 int /*<<< orphan*/  fdomain_make_bus_idle (struct fdomain*) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 struct fdomain* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int fdomain_select(struct Scsi_Host *sh, int target)
{
	int status;
	unsigned long timeout;
	struct fdomain *fd = shost_priv(sh);

	outb(BCTL_BUSEN | BCTL_SEL, fd->base + REG_BCTL);
	outb(BIT(sh->this_id) | BIT(target), fd->base + REG_SCSI_DATA_NOACK);

	/* Stop arbitration and enable parity */
	outb(PARITY_MASK, fd->base + REG_ACTL);

	timeout = 350;	/* 350 msec */

	do {
		status = inb(fd->base + REG_BSTAT);
		if (status & BSTAT_BSY) {
			/* Enable SCSI Bus */
			/* (on error, should make bus idle with 0) */
			outb(BCTL_BUSEN, fd->base + REG_BCTL);
			return 0;
		}
		mdelay(1);
	} while (--timeout);
	fdomain_make_bus_idle(fd);
	return 1;
}