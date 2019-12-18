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
 int /*<<< orphan*/  AF_CHPRST_DETECTED ; 
 int /*<<< orphan*/  AF_CHPRST_NEEDED ; 
 int /*<<< orphan*/  AF_CHPRST_STARTED ; 
 int /*<<< orphan*/  AF_DEGRADED_MODE ; 
 int /*<<< orphan*/  AF_FIRST_INIT ; 
 int /*<<< orphan*/  AF_POWER_MGT ; 
 int /*<<< orphan*/  ESAS2R_LOG_CRIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esas2r_check_adapter (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_disable_chip_interrupts (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_enable_chip_interrupts (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_init_adapter_hw (struct esas2r_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  esas2r_send_reset_ae (struct esas2r_adapter*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void esas2r_handle_chip_rst_during_tasklet(struct esas2r_adapter *a)
{
	while (test_bit(AF_CHPRST_DETECTED, &a->flags)) {
		/*
		 * Balance the enable in esas2r_initadapter_hw.
		 * Esas2r_power_down already took care of it for power
		 * management.
		 */
		if (!test_bit(AF_DEGRADED_MODE, &a->flags) &&
		    !test_bit(AF_POWER_MGT, &a->flags))
			esas2r_disable_chip_interrupts(a);

		/* Reinitialize the chip. */
		esas2r_check_adapter(a);
		esas2r_init_adapter_hw(a, 0);

		if (test_bit(AF_CHPRST_NEEDED, &a->flags))
			break;

		if (test_bit(AF_POWER_MGT, &a->flags)) {
			/* Recovery from power management. */
			if (test_bit(AF_FIRST_INIT, &a->flags)) {
				/* Chip reset during normal power up */
				esas2r_log(ESAS2R_LOG_CRIT,
					   "The firmware was reset during a normal power-up sequence");
			} else {
				/* Deferred power up complete. */
				clear_bit(AF_POWER_MGT, &a->flags);
				esas2r_send_reset_ae(a, true);
			}
		} else {
			/* Recovery from online chip reset. */
			if (test_bit(AF_FIRST_INIT, &a->flags)) {
				/* Chip reset during driver load */
			} else {
				/* Chip reset after driver load */
				esas2r_send_reset_ae(a, false);
			}

			esas2r_log(ESAS2R_LOG_CRIT,
				   "Recovering from a chip reset while the chip was online");
		}

		clear_bit(AF_CHPRST_STARTED, &a->flags);
		esas2r_enable_chip_interrupts(a);

		/*
		 * Clear this flag last!  this indicates that the chip has been
		 * reset already during initialization.
		 */
		clear_bit(AF_CHPRST_DETECTED, &a->flags);
	}
}