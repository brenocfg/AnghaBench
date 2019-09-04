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
struct sii8620 {int dummy; } ;
struct drm_display_mode {int clock; } ;

/* Variables and functions */
 int MHL1_MAX_PCLK ; 
 int MHL1_MAX_PCLK_PP_MODE ; 
 int MHL3_MAX_PCLK ; 
 int MHL3_MAX_PCLK_PP_MODE ; 
 scalar_t__ sii8620_is_mhl3 (struct sii8620*) ; 

__attribute__((used)) static int sii8620_is_packing_required(struct sii8620 *ctx,
				       const struct drm_display_mode *mode)
{
	int max_pclk, max_pclk_pp_mode;

	if (sii8620_is_mhl3(ctx)) {
		max_pclk = MHL3_MAX_PCLK;
		max_pclk_pp_mode = MHL3_MAX_PCLK_PP_MODE;
	} else {
		max_pclk = MHL1_MAX_PCLK;
		max_pclk_pp_mode = MHL1_MAX_PCLK_PP_MODE;
	}

	if (mode->clock < max_pclk)
		return 0;
	else if (mode->clock < max_pclk_pp_mode)
		return 1;
	else
		return -1;
}