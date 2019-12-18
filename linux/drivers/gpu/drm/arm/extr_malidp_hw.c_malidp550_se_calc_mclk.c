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
struct videomode {unsigned long pixelclock; unsigned long hactive; unsigned long hfront_porch; unsigned long hback_porch; unsigned long hsync_len; } ;
struct malidp_se_config {unsigned long output_w; unsigned long input_h; unsigned long output_h; int /*<<< orphan*/  input_w; scalar_t__ scale_enable; } ;
struct malidp_hw_device {int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,unsigned long) ; 
 long EINVAL ; 
 long clk_get_rate (int /*<<< orphan*/ ) ; 
 unsigned long max (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long min (unsigned long,unsigned long) ; 

__attribute__((used)) static long malidp550_se_calc_mclk(struct malidp_hw_device *hwdev,
				   struct malidp_se_config *se_config,
				   struct videomode *vm)
{
	unsigned long mclk;
	unsigned long pxlclk = vm->pixelclock;
	unsigned long htotal = vm->hactive + vm->hfront_porch +
			       vm->hback_porch + vm->hsync_len;
	unsigned long numerator = 1, denominator = 1;
	long ret;

	if (se_config->scale_enable) {
		numerator = max(se_config->input_w, se_config->output_w) *
			    se_config->input_h;
		numerator += se_config->output_w *
			     (se_config->output_h -
			      min(se_config->input_h, se_config->output_h));
		denominator = (htotal - 2) * se_config->output_h;
	}

	/* mclk can't be slower than pxlclk. */
	if (numerator < denominator)
		numerator = denominator = 1;
	mclk = (pxlclk * numerator) / denominator;
	ret = clk_get_rate(hwdev->mclk);
	if (ret < mclk) {
		DRM_DEBUG_DRIVER("mclk requirement of %lu kHz can't be met.\n",
				 mclk / 1000);
		return -EINVAL;
	}
	return ret;
}