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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {scalar_t__ len; } ;
struct cec_pin {TYPE_1__ tx_msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_ERROR_INJ_RX_ARB_LOST_ARG_IDX ; 
 int /*<<< orphan*/  CEC_ERROR_INJ_RX_ARB_LOST_OFFSET ; 
 scalar_t__ rx_error_inj (struct cec_pin*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool rx_arb_lost(struct cec_pin *pin, u8 *poll)
{
	return pin->tx_msg.len == 0 &&
		rx_error_inj(pin, CEC_ERROR_INJ_RX_ARB_LOST_OFFSET,
			     CEC_ERROR_INJ_RX_ARB_LOST_ARG_IDX, poll);
}