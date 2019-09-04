#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct scaler_context {int dummy; } ;
struct TYPE_4__ {int* pitch; } ;
struct exynos_drm_ipp_buffer {TYPE_2__ buf; TYPE_1__* format; } ;
struct TYPE_3__ {int* cpp; int num_planes; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCALER_DST_SPAN ; 
 int /*<<< orphan*/  SCALER_DST_SPAN_SET_C_SPAN (int) ; 
 int /*<<< orphan*/  SCALER_DST_SPAN_SET_Y_SPAN (int) ; 
 int /*<<< orphan*/  scaler_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void scaler_set_dst_span(struct scaler_context *scaler,
	struct exynos_drm_ipp_buffer *dst_buf)
{
	u32 val;

	val = SCALER_DST_SPAN_SET_Y_SPAN(dst_buf->buf.pitch[0] /
		dst_buf->format->cpp[0]);

	if (dst_buf->format->num_planes > 1)
		val |= SCALER_DST_SPAN_SET_C_SPAN(dst_buf->buf.pitch[1]);

	scaler_write(val, SCALER_DST_SPAN);
}