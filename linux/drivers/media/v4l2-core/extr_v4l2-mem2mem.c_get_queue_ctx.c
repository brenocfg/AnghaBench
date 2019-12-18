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
struct v4l2_m2m_queue_ctx {int dummy; } ;
struct v4l2_m2m_ctx {struct v4l2_m2m_queue_ctx cap_q_ctx; struct v4l2_m2m_queue_ctx out_q_ctx; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int) ; 

__attribute__((used)) static struct v4l2_m2m_queue_ctx *get_queue_ctx(struct v4l2_m2m_ctx *m2m_ctx,
						enum v4l2_buf_type type)
{
	if (V4L2_TYPE_IS_OUTPUT(type))
		return &m2m_ctx->out_q_ctx;
	else
		return &m2m_ctx->cap_q_ctx;
}