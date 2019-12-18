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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmw_sw_context {int dummy; } ;
struct vmw_private {int dummy; } ;
struct vmw_buffer_object {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ SVGAFifoCmdDefineGMRFB ;

/* Variables and functions */
 int vmw_translate_guest_ptr (struct vmw_private*,struct vmw_sw_context*,int /*<<< orphan*/ *,struct vmw_buffer_object**) ; 

__attribute__((used)) static int vmw_cmd_check_define_gmrfb(struct vmw_private *dev_priv,
				      struct vmw_sw_context *sw_context,
				      void *buf)
{
	struct vmw_buffer_object *vmw_bo;

	struct {
		uint32_t header;
		SVGAFifoCmdDefineGMRFB body;
	} *cmd = buf;

	return vmw_translate_guest_ptr(dev_priv, sw_context, &cmd->body.ptr,
				       &vmw_bo);
}