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
struct s5p_mfc_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CROP_INFO_H ; 
 unsigned int s5p_mfc_read_info_v5 (struct s5p_mfc_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int s5p_mfc_get_crop_info_h_v5(struct s5p_mfc_ctx *ctx)
{
	return s5p_mfc_read_info_v5(ctx, CROP_INFO_H);
}