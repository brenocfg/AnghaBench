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
struct coda_q_data {int dummy; } ;
struct coda_ctx {struct coda_q_data* q_data; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 129 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT 128 
 size_t V4L2_M2M_DST ; 
 size_t V4L2_M2M_SRC ; 

__attribute__((used)) static inline struct coda_q_data *get_q_data(struct coda_ctx *ctx,
					     enum v4l2_buf_type type)
{
	switch (type) {
	case V4L2_BUF_TYPE_VIDEO_OUTPUT:
		return &(ctx->q_data[V4L2_M2M_SRC]);
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
		return &(ctx->q_data[V4L2_M2M_DST]);
	default:
		return NULL;
	}
}