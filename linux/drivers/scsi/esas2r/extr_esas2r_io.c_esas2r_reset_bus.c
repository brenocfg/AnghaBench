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
struct esas2r_adapter {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_BUSRST_NEEDED ; 
 int /*<<< orphan*/  AF_BUSRST_PENDING ; 
 int /*<<< orphan*/  AF_CHPRST_PENDING ; 
 int /*<<< orphan*/  AF_DEGRADED_MODE ; 
 int /*<<< orphan*/  AF_DISC_PENDING ; 
 int /*<<< orphan*/  AF_OS_RESET ; 
 int /*<<< orphan*/  ESAS2R_LOG_INFO ; 
 int /*<<< orphan*/  esas2r_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  esas2r_schedule_tasklet (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void esas2r_reset_bus(struct esas2r_adapter *a)
{
	esas2r_log(ESAS2R_LOG_INFO, "performing a bus reset");

	if (!test_bit(AF_DEGRADED_MODE, &a->flags) &&
	    !test_bit(AF_CHPRST_PENDING, &a->flags) &&
	    !test_bit(AF_DISC_PENDING, &a->flags)) {
		set_bit(AF_BUSRST_NEEDED, &a->flags);
		set_bit(AF_BUSRST_PENDING, &a->flags);
		set_bit(AF_OS_RESET, &a->flags);

		esas2r_schedule_tasklet(a);
	}
}