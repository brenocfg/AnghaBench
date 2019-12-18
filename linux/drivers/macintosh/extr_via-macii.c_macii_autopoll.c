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
struct adb_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADBREQ_NOSEND ; 
 int /*<<< orphan*/  ADB_READREG (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adb_request (struct adb_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int autopoll_devs ; 
 int /*<<< orphan*/ * current_req ; 
 scalar_t__ ffs (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int macii_write (struct adb_request*) ; 

__attribute__((used)) static int macii_autopoll(int devs)
{
	static struct adb_request req;
	unsigned long flags;
	int err = 0;

	/* bit 1 == device 1, and so on. */
	autopoll_devs = devs & 0xFFFE;

	if (!autopoll_devs)
		return 0;

	local_irq_save(flags);

	if (current_req == NULL) {
		/* Send a Talk Reg 0. The controller will repeatedly transmit
		 * this as long as it is idle.
		 */
		adb_request(&req, NULL, ADBREQ_NOSEND, 1,
		            ADB_READREG(ffs(autopoll_devs) - 1, 0));
		err = macii_write(&req);
	}

	local_irq_restore(flags);
	return err;
}