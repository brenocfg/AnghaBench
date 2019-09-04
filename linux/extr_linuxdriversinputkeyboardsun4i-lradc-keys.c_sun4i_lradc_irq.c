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
typedef  int u32 ;
struct sun4i_lradc_data {scalar_t__ chan0_keycode; int vref; int chan0_map_count; scalar_t__ base; int /*<<< orphan*/  input; TYPE_1__* chan0_map; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int keycode; scalar_t__ voltage; } ;

/* Variables and functions */
 int CHAN0_KEYDOWN_IRQ ; 
 int CHAN0_KEYUP_IRQ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ LRADC_DATA0 ; 
 scalar_t__ LRADC_INTS ; 
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t sun4i_lradc_irq(int irq, void *dev_id)
{
	struct sun4i_lradc_data *lradc = dev_id;
	u32 i, ints, val, voltage, diff, keycode = 0, closest = 0xffffffff;

	ints  = readl(lradc->base + LRADC_INTS);

	/*
	 * lradc supports only one keypress at a time, release does not give
	 * any info as to which key was released, so we cache the keycode.
	 */

	if (ints & CHAN0_KEYUP_IRQ) {
		input_report_key(lradc->input, lradc->chan0_keycode, 0);
		lradc->chan0_keycode = 0;
	}

	if ((ints & CHAN0_KEYDOWN_IRQ) && lradc->chan0_keycode == 0) {
		val = readl(lradc->base + LRADC_DATA0) & 0x3f;
		voltage = val * lradc->vref / 63;

		for (i = 0; i < lradc->chan0_map_count; i++) {
			diff = abs(lradc->chan0_map[i].voltage - voltage);
			if (diff < closest) {
				closest = diff;
				keycode = lradc->chan0_map[i].keycode;
			}
		}

		lradc->chan0_keycode = keycode;
		input_report_key(lradc->input, lradc->chan0_keycode, 1);
	}

	input_sync(lradc->input);

	writel(ints, lradc->base + LRADC_INTS);

	return IRQ_HANDLED;
}