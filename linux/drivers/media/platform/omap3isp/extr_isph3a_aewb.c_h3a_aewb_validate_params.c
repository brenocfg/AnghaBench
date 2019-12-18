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
typedef  scalar_t__ u32 ;
struct omap3isp_h3a_aewb_config {scalar_t__ saturation_limit; int win_height; int win_width; scalar_t__ ver_win_count; scalar_t__ hor_win_count; scalar_t__ ver_win_start; scalar_t__ hor_win_start; scalar_t__ blk_ver_win_start; int blk_win_height; int subsample_ver_inc; int subsample_hor_inc; scalar_t__ buf_size; } ;
struct ispstat {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ OMAP3ISP_AEWB_MAX_BUF_SIZE ; 
 scalar_t__ OMAP3ISP_AEWB_MAX_SATURATION_LIM ; 
 int OMAP3ISP_AEWB_MAX_SUB_INC ; 
 scalar_t__ OMAP3ISP_AEWB_MAX_WINHC ; 
 scalar_t__ OMAP3ISP_AEWB_MAX_WINSTART ; 
 scalar_t__ OMAP3ISP_AEWB_MAX_WINVC ; 
 int OMAP3ISP_AEWB_MAX_WIN_H ; 
 int OMAP3ISP_AEWB_MAX_WIN_W ; 
 int OMAP3ISP_AEWB_MIN_SUB_INC ; 
 scalar_t__ OMAP3ISP_AEWB_MIN_WINHC ; 
 scalar_t__ OMAP3ISP_AEWB_MIN_WINVC ; 
 int OMAP3ISP_AEWB_MIN_WIN_H ; 
 int OMAP3ISP_AEWB_MIN_WIN_W ; 
 scalar_t__ h3a_aewb_get_buf_size (struct omap3isp_h3a_aewb_config*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int h3a_aewb_validate_params(struct ispstat *aewb, void *new_conf)
{
	struct omap3isp_h3a_aewb_config *user_cfg = new_conf;
	u32 buf_size;

	if (unlikely(user_cfg->saturation_limit >
		     OMAP3ISP_AEWB_MAX_SATURATION_LIM))
		return -EINVAL;

	if (unlikely(user_cfg->win_height < OMAP3ISP_AEWB_MIN_WIN_H ||
		     user_cfg->win_height > OMAP3ISP_AEWB_MAX_WIN_H ||
		     user_cfg->win_height & 0x01))
		return -EINVAL;

	if (unlikely(user_cfg->win_width < OMAP3ISP_AEWB_MIN_WIN_W ||
		     user_cfg->win_width > OMAP3ISP_AEWB_MAX_WIN_W ||
		     user_cfg->win_width & 0x01))
		return -EINVAL;

	if (unlikely(user_cfg->ver_win_count < OMAP3ISP_AEWB_MIN_WINVC ||
		     user_cfg->ver_win_count > OMAP3ISP_AEWB_MAX_WINVC))
		return -EINVAL;

	if (unlikely(user_cfg->hor_win_count < OMAP3ISP_AEWB_MIN_WINHC ||
		     user_cfg->hor_win_count > OMAP3ISP_AEWB_MAX_WINHC))
		return -EINVAL;

	if (unlikely(user_cfg->ver_win_start > OMAP3ISP_AEWB_MAX_WINSTART))
		return -EINVAL;

	if (unlikely(user_cfg->hor_win_start > OMAP3ISP_AEWB_MAX_WINSTART))
		return -EINVAL;

	if (unlikely(user_cfg->blk_ver_win_start > OMAP3ISP_AEWB_MAX_WINSTART))
		return -EINVAL;

	if (unlikely(user_cfg->blk_win_height < OMAP3ISP_AEWB_MIN_WIN_H ||
		     user_cfg->blk_win_height > OMAP3ISP_AEWB_MAX_WIN_H ||
		     user_cfg->blk_win_height & 0x01))
		return -EINVAL;

	if (unlikely(user_cfg->subsample_ver_inc < OMAP3ISP_AEWB_MIN_SUB_INC ||
		     user_cfg->subsample_ver_inc > OMAP3ISP_AEWB_MAX_SUB_INC ||
		     user_cfg->subsample_ver_inc & 0x01))
		return -EINVAL;

	if (unlikely(user_cfg->subsample_hor_inc < OMAP3ISP_AEWB_MIN_SUB_INC ||
		     user_cfg->subsample_hor_inc > OMAP3ISP_AEWB_MAX_SUB_INC ||
		     user_cfg->subsample_hor_inc & 0x01))
		return -EINVAL;

	buf_size = h3a_aewb_get_buf_size(user_cfg);
	if (buf_size > user_cfg->buf_size)
		user_cfg->buf_size = buf_size;
	else if (user_cfg->buf_size > OMAP3ISP_AEWB_MAX_BUF_SIZE)
		user_cfg->buf_size = OMAP3ISP_AEWB_MAX_BUF_SIZE;

	return 0;
}