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
typedef  int u32 ;
struct cx18_stream {int /*<<< orphan*/  handle; struct cx18* cx; } ;
struct cx18 {int filter_mode; scalar_t__ temporal_strength; scalar_t__ spatial_strength; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_CPU_SET_FILTER_PARAM ; 
 int cx18_vapi (struct cx18*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,scalar_t__) ; 

__attribute__((used)) static int cx18_set_filter_param(struct cx18_stream *s)
{
	struct cx18 *cx = s->cx;
	u32 mode;
	int ret;

	mode = (cx->filter_mode & 1) ? 2 : (cx->spatial_strength ? 1 : 0);
	ret = cx18_vapi(cx, CX18_CPU_SET_FILTER_PARAM, 4,
			s->handle, 1, mode, cx->spatial_strength);
	mode = (cx->filter_mode & 2) ? 2 : (cx->temporal_strength ? 1 : 0);
	ret = ret ? ret : cx18_vapi(cx, CX18_CPU_SET_FILTER_PARAM, 4,
			s->handle, 0, mode, cx->temporal_strength);
	ret = ret ? ret : cx18_vapi(cx, CX18_CPU_SET_FILTER_PARAM, 4,
			s->handle, 2, cx->filter_mode >> 2, 0);
	return ret;
}