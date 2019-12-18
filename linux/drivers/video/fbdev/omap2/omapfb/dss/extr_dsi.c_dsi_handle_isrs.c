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
typedef  scalar_t__ u32 ;
struct dsi_isr_tables {int /*<<< orphan*/  isr_table_cio; int /*<<< orphan*/ * isr_table_vc; int /*<<< orphan*/  isr_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_call_isrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void dsi_handle_isrs(struct dsi_isr_tables *isr_tables,
		u32 irqstatus, u32 *vcstatus, u32 ciostatus)
{
	int i;

	dsi_call_isrs(isr_tables->isr_table,
			ARRAY_SIZE(isr_tables->isr_table),
			irqstatus);

	for (i = 0; i < 4; ++i) {
		if (vcstatus[i] == 0)
			continue;
		dsi_call_isrs(isr_tables->isr_table_vc[i],
				ARRAY_SIZE(isr_tables->isr_table_vc[i]),
				vcstatus[i]);
	}

	if (ciostatus != 0)
		dsi_call_isrs(isr_tables->isr_table_cio,
				ARRAY_SIZE(isr_tables->isr_table_cio),
				ciostatus);
}