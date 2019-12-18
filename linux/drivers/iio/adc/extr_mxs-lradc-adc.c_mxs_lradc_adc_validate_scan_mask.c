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
struct mxs_lradc_adc {struct mxs_lradc* lradc; } ;
struct mxs_lradc {scalar_t__ touchscreen_wire; scalar_t__ use_touchbutton; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 unsigned long CHAN_MASK_TOUCHBUTTON ; 
 unsigned long CHAN_MASK_TOUCHSCREEN_4WIRE ; 
 unsigned long CHAN_MASK_TOUCHSCREEN_5WIRE ; 
 int const LRADC_MAX_MAPPED_CHANS ; 
 int /*<<< orphan*/  LRADC_MAX_TOTAL_CHANS ; 
 scalar_t__ MXS_LRADC_TOUCHSCREEN_4WIRE ; 
 scalar_t__ MXS_LRADC_TOUCHSCREEN_5WIRE ; 
 scalar_t__ bitmap_intersects (unsigned long const*,unsigned long*,int /*<<< orphan*/ ) ; 
 int bitmap_weight (unsigned long const*,int /*<<< orphan*/ ) ; 
 struct mxs_lradc_adc* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static bool mxs_lradc_adc_validate_scan_mask(struct iio_dev *iio,
					     const unsigned long *mask)
{
	struct mxs_lradc_adc *adc = iio_priv(iio);
	struct mxs_lradc *lradc = adc->lradc;
	const int map_chans = bitmap_weight(mask, LRADC_MAX_TOTAL_CHANS);
	int rsvd_chans = 0;
	unsigned long rsvd_mask = 0;

	if (lradc->use_touchbutton)
		rsvd_mask |= CHAN_MASK_TOUCHBUTTON;
	if (lradc->touchscreen_wire == MXS_LRADC_TOUCHSCREEN_4WIRE)
		rsvd_mask |= CHAN_MASK_TOUCHSCREEN_4WIRE;
	if (lradc->touchscreen_wire == MXS_LRADC_TOUCHSCREEN_5WIRE)
		rsvd_mask |= CHAN_MASK_TOUCHSCREEN_5WIRE;

	if (lradc->use_touchbutton)
		rsvd_chans++;
	if (lradc->touchscreen_wire)
		rsvd_chans += 2;

	/* Test for attempts to map channels with special mode of operation. */
	if (bitmap_intersects(mask, &rsvd_mask, LRADC_MAX_TOTAL_CHANS))
		return false;

	/* Test for attempts to map more channels then available slots. */
	if (map_chans + rsvd_chans > LRADC_MAX_MAPPED_CHANS)
		return false;

	return true;
}