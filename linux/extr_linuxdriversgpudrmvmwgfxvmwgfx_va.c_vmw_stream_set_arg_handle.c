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
typedef  int /*<<< orphan*/  u32 ;
struct drm_vmw_stream_arg {int /*<<< orphan*/  stream_id; } ;

/* Variables and functions */

__attribute__((used)) static void vmw_stream_set_arg_handle(void *data, u32 handle)
{
	struct drm_vmw_stream_arg *arg = (struct drm_vmw_stream_arg *)data;

	arg->stream_id = handle;
}