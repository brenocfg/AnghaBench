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
struct drm_display_mode {int dummy; } ;
struct armada_crtc {int /*<<< orphan*/  clk; int /*<<< orphan*/ * extclk; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void armada510_crtc_enable(struct armada_crtc *dcrtc,
	const struct drm_display_mode *mode)
{
	if (IS_ERR(dcrtc->clk)) {
		dcrtc->clk = dcrtc->extclk[0];
		WARN_ON(clk_prepare_enable(dcrtc->clk));
	}
}