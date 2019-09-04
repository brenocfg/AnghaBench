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
struct sti_hqvdp {int /*<<< orphan*/  clk; } ;
struct drm_display_mode {int htotal; int clock; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int,int) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int max (int,int) ; 

__attribute__((used)) static bool sti_hqvdp_check_hw_scaling(struct sti_hqvdp *hqvdp,
				       struct drm_display_mode *mode,
				       int src_w, int src_h,
				       int dst_w, int dst_h)
{
	unsigned long lfw;
	unsigned int inv_zy;

	lfw = mode->htotal * (clk_get_rate(hqvdp->clk) / 1000000);
	lfw /= max(src_w, dst_w) * mode->clock / 1000;

	inv_zy = DIV_ROUND_UP(src_h, dst_h);

	return (inv_zy <= lfw) ? true : false;
}