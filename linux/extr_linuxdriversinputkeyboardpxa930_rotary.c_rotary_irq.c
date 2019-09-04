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
struct pxa930_rotary_platform_data {int up_key; int down_key; int /*<<< orphan*/  rel_code; } ;
struct pxa930_rotary {int last_ercr; int /*<<< orphan*/  input_dev; scalar_t__ mmio_base; struct pxa930_rotary_platform_data* pdata; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ ERCR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  clear_sbcr (struct pxa930_rotary*) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  input_report_rel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t rotary_irq(int irq, void *dev_id)
{
	struct pxa930_rotary *r = dev_id;
	struct pxa930_rotary_platform_data *pdata = r->pdata;
	int ercr, delta, key;

	ercr = __raw_readl(r->mmio_base + ERCR) & 0xf;
	clear_sbcr(r);

	delta = ercr - r->last_ercr;
	if (delta == 0)
		return IRQ_HANDLED;

	r->last_ercr = ercr;

	if (pdata->up_key && pdata->down_key) {
		key = (delta > 0) ? pdata->up_key : pdata->down_key;
		input_report_key(r->input_dev, key, 1);
		input_sync(r->input_dev);
		input_report_key(r->input_dev, key, 0);
	} else
		input_report_rel(r->input_dev, pdata->rel_code, delta);

	input_sync(r->input_dev);

	return IRQ_HANDLED;
}