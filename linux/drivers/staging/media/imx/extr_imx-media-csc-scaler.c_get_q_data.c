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
struct ipu_csc_scaler_q_data {int dummy; } ;
struct ipu_csc_scaler_ctx {struct ipu_csc_scaler_q_data* q_data; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 size_t V4L2_M2M_DST ; 
 size_t V4L2_M2M_SRC ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int) ; 

__attribute__((used)) static struct ipu_csc_scaler_q_data *get_q_data(struct ipu_csc_scaler_ctx *ctx,
						enum v4l2_buf_type type)
{
	if (V4L2_TYPE_IS_OUTPUT(type))
		return &ctx->q_data[V4L2_M2M_SRC];
	else
		return &ctx->q_data[V4L2_M2M_DST];
}