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
struct omap3isp_h3a_aewb_config {scalar_t__ saturation_limit; scalar_t__ alaw_enable; scalar_t__ win_height; scalar_t__ win_width; scalar_t__ ver_win_count; scalar_t__ hor_win_count; scalar_t__ ver_win_start; scalar_t__ hor_win_start; scalar_t__ blk_ver_win_start; scalar_t__ blk_win_height; scalar_t__ subsample_ver_inc; scalar_t__ subsample_hor_inc; int /*<<< orphan*/  buf_size; } ;
struct ispstat {int update; int /*<<< orphan*/  inc_config; int /*<<< orphan*/  configured; struct omap3isp_h3a_aewb_config* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  h3a_aewb_get_buf_size (struct omap3isp_h3a_aewb_config*) ; 

__attribute__((used)) static void h3a_aewb_set_params(struct ispstat *aewb, void *new_conf)
{
	struct omap3isp_h3a_aewb_config *user_cfg = new_conf;
	struct omap3isp_h3a_aewb_config *cur_cfg = aewb->priv;
	int update = 0;

	if (cur_cfg->saturation_limit != user_cfg->saturation_limit) {
		cur_cfg->saturation_limit = user_cfg->saturation_limit;
		update = 1;
	}
	if (cur_cfg->alaw_enable != user_cfg->alaw_enable) {
		cur_cfg->alaw_enable = user_cfg->alaw_enable;
		update = 1;
	}
	if (cur_cfg->win_height != user_cfg->win_height) {
		cur_cfg->win_height = user_cfg->win_height;
		update = 1;
	}
	if (cur_cfg->win_width != user_cfg->win_width) {
		cur_cfg->win_width = user_cfg->win_width;
		update = 1;
	}
	if (cur_cfg->ver_win_count != user_cfg->ver_win_count) {
		cur_cfg->ver_win_count = user_cfg->ver_win_count;
		update = 1;
	}
	if (cur_cfg->hor_win_count != user_cfg->hor_win_count) {
		cur_cfg->hor_win_count = user_cfg->hor_win_count;
		update = 1;
	}
	if (cur_cfg->ver_win_start != user_cfg->ver_win_start) {
		cur_cfg->ver_win_start = user_cfg->ver_win_start;
		update = 1;
	}
	if (cur_cfg->hor_win_start != user_cfg->hor_win_start) {
		cur_cfg->hor_win_start = user_cfg->hor_win_start;
		update = 1;
	}
	if (cur_cfg->blk_ver_win_start != user_cfg->blk_ver_win_start) {
		cur_cfg->blk_ver_win_start = user_cfg->blk_ver_win_start;
		update = 1;
	}
	if (cur_cfg->blk_win_height != user_cfg->blk_win_height) {
		cur_cfg->blk_win_height = user_cfg->blk_win_height;
		update = 1;
	}
	if (cur_cfg->subsample_ver_inc != user_cfg->subsample_ver_inc) {
		cur_cfg->subsample_ver_inc = user_cfg->subsample_ver_inc;
		update = 1;
	}
	if (cur_cfg->subsample_hor_inc != user_cfg->subsample_hor_inc) {
		cur_cfg->subsample_hor_inc = user_cfg->subsample_hor_inc;
		update = 1;
	}

	if (update || !aewb->configured) {
		aewb->inc_config++;
		aewb->update = 1;
		cur_cfg->buf_size = h3a_aewb_get_buf_size(cur_cfg);
	}
}