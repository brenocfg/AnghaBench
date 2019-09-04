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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  XIVE_SRC_SET_EISN ; 
 long plpar_int_set_source_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xive_spapr_configure_irq(u32 hw_irq, u32 target, u8 prio, u32 sw_irq)
{
	long rc;

	rc = plpar_int_set_source_config(XIVE_SRC_SET_EISN, hw_irq, target,
					 prio, sw_irq);

	return rc == 0 ? 0 : -ENXIO;
}