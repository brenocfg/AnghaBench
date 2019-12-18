#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int width; unsigned int height; } ;
struct vpe_q_data {TYPE_1__ c_rect; } ;
struct vpe_ctx {struct vpe_q_data* q_data; } ;

/* Variables and functions */
 size_t Q_DATA_DST ; 
 size_t Q_DATA_SRC ; 
 unsigned int SC_MAX_PIXEL_HEIGHT ; 
 unsigned int SC_MAX_PIXEL_WIDTH ; 

__attribute__((used)) static int check_srcdst_sizes(struct vpe_ctx *ctx)
{
	struct vpe_q_data *s_q_data =  &ctx->q_data[Q_DATA_SRC];
	struct vpe_q_data *d_q_data =  &ctx->q_data[Q_DATA_DST];
	unsigned int src_w = s_q_data->c_rect.width;
	unsigned int src_h = s_q_data->c_rect.height;
	unsigned int dst_w = d_q_data->c_rect.width;
	unsigned int dst_h = d_q_data->c_rect.height;

	if (src_w == dst_w && src_h == dst_h)
		return 0;

	if (src_h <= SC_MAX_PIXEL_HEIGHT &&
	    src_w <= SC_MAX_PIXEL_WIDTH &&
	    dst_h <= SC_MAX_PIXEL_HEIGHT &&
	    dst_w <= SC_MAX_PIXEL_WIDTH)
		return 0;

	return -1;
}