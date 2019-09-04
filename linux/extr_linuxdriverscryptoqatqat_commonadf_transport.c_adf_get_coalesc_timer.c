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
typedef  int /*<<< orphan*/  uint32_t ;
struct adf_etr_bank_data {scalar_t__ irq_coalesc_timer; int /*<<< orphan*/  accel_dev; } ;

/* Variables and functions */
 void* ADF_COALESCING_DEF_TIME ; 
 scalar_t__ ADF_COALESCING_MAX_TIME ; 
 scalar_t__ ADF_COALESCING_MIN_TIME ; 
 int /*<<< orphan*/  ADF_ETRMGR_COALESCE_TIMER_FORMAT ; 
 scalar_t__ adf_get_cfg_int (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void adf_get_coalesc_timer(struct adf_etr_bank_data *bank,
				  const char *section,
				  uint32_t bank_num_in_accel)
{
	if (adf_get_cfg_int(bank->accel_dev, section,
			    ADF_ETRMGR_COALESCE_TIMER_FORMAT,
			    bank_num_in_accel, &bank->irq_coalesc_timer))
		bank->irq_coalesc_timer = ADF_COALESCING_DEF_TIME;

	if (ADF_COALESCING_MAX_TIME < bank->irq_coalesc_timer ||
	    ADF_COALESCING_MIN_TIME > bank->irq_coalesc_timer)
		bank->irq_coalesc_timer = ADF_COALESCING_DEF_TIME;
}