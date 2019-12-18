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
struct hinic_hwif {int /*<<< orphan*/  cfg_regs_bar; int /*<<< orphan*/  intr_regs_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 

void hinic_free_hwif(struct hinic_hwif *hwif)
{
	iounmap(hwif->intr_regs_base);
	iounmap(hwif->cfg_regs_bar);
}