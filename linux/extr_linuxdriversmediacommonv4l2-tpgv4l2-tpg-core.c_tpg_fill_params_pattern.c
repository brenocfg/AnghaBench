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
struct tpg_draw_params {int mv_vert_old; int mv_vert_new; void* mv_hor_new; void* mv_hor_old; } ;
struct tpg_data {int mv_hor_count; int src_width; int mv_hor_step; int mv_vert_count; int src_height; int mv_vert_step; } ;

/* Variables and functions */
 void* tpg_hscale_div (struct tpg_data const*,unsigned int,int) ; 

__attribute__((used)) static void tpg_fill_params_pattern(const struct tpg_data *tpg, unsigned p,
				    struct tpg_draw_params *params)
{
	params->mv_hor_old =
		tpg_hscale_div(tpg, p, tpg->mv_hor_count % tpg->src_width);
	params->mv_hor_new =
		tpg_hscale_div(tpg, p, (tpg->mv_hor_count + tpg->mv_hor_step) %
			       tpg->src_width);
	params->mv_vert_old = tpg->mv_vert_count % tpg->src_height;
	params->mv_vert_new =
		(tpg->mv_vert_count + tpg->mv_vert_step) % tpg->src_height;
}