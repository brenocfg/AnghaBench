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
struct tegra_vde {int /*<<< orphan*/  decode_completion; int /*<<< orphan*/  frameid; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ completion_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_vde_set_bits (struct tegra_vde*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t tegra_vde_isr(int irq, void *data)
{
	struct tegra_vde *vde = data;

	if (completion_done(&vde->decode_completion))
		return IRQ_NONE;

	tegra_vde_set_bits(vde, 0, vde->frameid, 0x208);
	complete(&vde->decode_completion);

	return IRQ_HANDLED;
}