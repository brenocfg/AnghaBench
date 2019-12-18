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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  H_CONTROL_CA_FUNCTION_GET_FUNCTION_ERR_INT ; 
 long cxl_h_control_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

long cxl_h_get_fn_error_interrupt(u64 unit_address, u64 *reg)
{
	return cxl_h_control_function(unit_address,
				H_CONTROL_CA_FUNCTION_GET_FUNCTION_ERR_INT,
				0, 0, 0, 0, reg);
}