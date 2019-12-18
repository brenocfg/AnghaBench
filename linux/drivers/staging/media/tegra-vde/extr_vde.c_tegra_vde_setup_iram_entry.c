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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_vde {int /*<<< orphan*/ * iram; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_vde_setup_iram_entry (unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_vde_setup_iram_entry(struct tegra_vde *vde,
				       unsigned int table,
				       unsigned int row,
				       u32 value1, u32 value2)
{
	u32 *iram_tables = vde->iram;

	trace_vde_setup_iram_entry(table, row, value1, value2);

	iram_tables[0x20 * table + row * 2] = value1;
	iram_tables[0x20 * table + row * 2 + 1] = value2;
}