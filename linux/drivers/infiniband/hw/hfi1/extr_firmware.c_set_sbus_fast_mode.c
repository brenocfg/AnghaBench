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
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_CFG_SBUS_EXECUTE ; 
 int /*<<< orphan*/  ASIC_CFG_SBUS_EXECUTE_FAST_MODE_SMASK ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void set_sbus_fast_mode(struct hfi1_devdata *dd)
{
	write_csr(dd, ASIC_CFG_SBUS_EXECUTE,
		  ASIC_CFG_SBUS_EXECUTE_FAST_MODE_SMASK);
}