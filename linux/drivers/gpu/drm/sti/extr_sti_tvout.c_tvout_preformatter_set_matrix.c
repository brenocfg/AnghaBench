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
typedef  int /*<<< orphan*/  u32 ;
struct sti_tvout {int dummy; } ;
struct drm_display_mode {scalar_t__ vdisplay; } ;

/* Variables and functions */
 scalar_t__ TVO_CSC_AUX_M0 ; 
 scalar_t__ TVO_CSC_MAIN_M0 ; 
 scalar_t__ TVO_MIN_HD_HEIGHT ; 
 int /*<<< orphan*/ * rgb_to_ycbcr_601 ; 
 int /*<<< orphan*/ * rgb_to_ycbcr_709 ; 
 int /*<<< orphan*/  tvout_write (struct sti_tvout*,int /*<<< orphan*/  const,scalar_t__) ; 

__attribute__((used)) static void tvout_preformatter_set_matrix(struct sti_tvout *tvout,
					  struct drm_display_mode *mode)
{
	unsigned int i;
	const u32 *pf_matrix;

	if (mode->vdisplay >= TVO_MIN_HD_HEIGHT)
		pf_matrix = rgb_to_ycbcr_709;
	else
		pf_matrix = rgb_to_ycbcr_601;

	for (i = 0; i < 8; i++) {
		tvout_write(tvout, *(pf_matrix + i),
			    TVO_CSC_MAIN_M0 + (i * 4));
		tvout_write(tvout, *(pf_matrix + i),
			    TVO_CSC_AUX_M0 + (i * 4));
	}
}