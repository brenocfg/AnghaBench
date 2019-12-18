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
struct lp8788_charger {int /*<<< orphan*/ ** chan; } ;

/* Variables and functions */
 int LP8788_NUM_CHG_ADC ; 
 int /*<<< orphan*/  iio_channel_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lp8788_release_adc_channel(struct lp8788_charger *pchg)
{
	int i;

	for (i = 0; i < LP8788_NUM_CHG_ADC; i++) {
		if (!pchg->chan[i])
			continue;

		iio_channel_release(pchg->chan[i]);
		pchg->chan[i] = NULL;
	}
}