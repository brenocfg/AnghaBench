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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmw_stream {int /*<<< orphan*/  stream_id; } ;
struct vmw_resource {int dummy; } ;
struct vmw_private {int dummy; } ;
struct ttm_object_file {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct vmw_resource*) ; 
 int PTR_ERR (struct vmw_resource*) ; 
 int /*<<< orphan*/  va_stream_func ; 
 struct vmw_resource* vmw_simple_resource_lookup (struct ttm_object_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vmw_stream* vmw_stream (struct vmw_resource*) ; 

int vmw_user_stream_lookup(struct vmw_private *dev_priv,
			   struct ttm_object_file *tfile,
			   uint32_t *inout_id, struct vmw_resource **out)
{
	struct vmw_stream *stream;
	struct vmw_resource *res =
		vmw_simple_resource_lookup(tfile, *inout_id, &va_stream_func);

	if (IS_ERR(res))
		return PTR_ERR(res);

	stream = vmw_stream(res);
	*inout_id = stream->stream_id;
	*out = res;

	return 0;
}