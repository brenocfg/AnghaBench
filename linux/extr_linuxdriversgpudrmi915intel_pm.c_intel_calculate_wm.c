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
struct intel_watermark_params {int guard_size; int max_wm; int default_wm; int /*<<< orphan*/  cacheline_size; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int intel_wm_method1 (int,int,unsigned int) ; 

__attribute__((used)) static unsigned int intel_calculate_wm(int pixel_rate,
				       const struct intel_watermark_params *wm,
				       int fifo_size, int cpp,
				       unsigned int latency_ns)
{
	int entries, wm_size;

	/*
	 * Note: we need to make sure we don't overflow for various clock &
	 * latency values.
	 * clocks go from a few thousand to several hundred thousand.
	 * latency is usually a few thousand
	 */
	entries = intel_wm_method1(pixel_rate, cpp,
				   latency_ns / 100);
	entries = DIV_ROUND_UP(entries, wm->cacheline_size) +
		wm->guard_size;
	DRM_DEBUG_KMS("FIFO entries required for mode: %d\n", entries);

	wm_size = fifo_size - entries;
	DRM_DEBUG_KMS("FIFO watermark level: %d\n", wm_size);

	/* Don't promote wm_size to unsigned... */
	if (wm_size > wm->max_wm)
		wm_size = wm->max_wm;
	if (wm_size <= 0)
		wm_size = wm->default_wm;

	/*
	 * Bspec seems to indicate that the value shouldn't be lower than
	 * 'burst size + 1'. Certainly 830 is quite unhappy with low values.
	 * Lets go for 8 which is the burst size since certain platforms
	 * already use a hardcoded 8 (which is what the spec says should be
	 * done).
	 */
	if (wm_size <= 8)
		wm_size = 8;

	return wm_size;
}