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
struct ad7879 {int /*<<< orphan*/  timer; int /*<<< orphan*/  conversion_data; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  AD7879_NR_SENSE ; 
 int /*<<< orphan*/  AD7879_REG_XPLUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ TS_PEN_UP_TIMEOUT ; 
 int /*<<< orphan*/  ad7879_report (struct ad7879*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ad7879_irq(int irq, void *handle)
{
	struct ad7879 *ts = handle;

	regmap_bulk_read(ts->regmap, AD7879_REG_XPLUS,
			 ts->conversion_data, AD7879_NR_SENSE);

	if (!ad7879_report(ts))
		mod_timer(&ts->timer, jiffies + TS_PEN_UP_TIMEOUT);

	return IRQ_HANDLED;
}