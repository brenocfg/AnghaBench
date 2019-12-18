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
struct cec_pin {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_ERROR_INJ_TX_EARLY_EOM_OFFSET ; 
 int tx_error_inj (struct cec_pin*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool tx_early_eom(struct cec_pin *pin)
{
	return tx_error_inj(pin, CEC_ERROR_INJ_TX_EARLY_EOM_OFFSET, -1, NULL);
}