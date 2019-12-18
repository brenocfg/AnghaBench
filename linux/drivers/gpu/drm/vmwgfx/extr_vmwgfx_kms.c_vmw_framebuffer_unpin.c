#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vmw_private {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct vmw_framebuffer {TYPE_4__ base; scalar_t__ bo; } ;
struct vmw_buffer_object {int dummy; } ;
struct TYPE_11__ {struct vmw_buffer_object* buffer; } ;
struct TYPE_9__ {TYPE_2__* surface; } ;
struct TYPE_7__ {struct vmw_buffer_object* backup; } ;
struct TYPE_8__ {TYPE_1__ res; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int vmw_bo_unpin (struct vmw_private*,struct vmw_buffer_object*,int) ; 
 TYPE_5__* vmw_framebuffer_to_vfbd (TYPE_4__*) ; 
 TYPE_3__* vmw_framebuffer_to_vfbs (TYPE_4__*) ; 
 struct vmw_private* vmw_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmw_framebuffer_unpin(struct vmw_framebuffer *vfb)
{
	struct vmw_private *dev_priv = vmw_priv(vfb->base.dev);
	struct vmw_buffer_object *buf;

	buf = vfb->bo ?  vmw_framebuffer_to_vfbd(&vfb->base)->buffer :
		vmw_framebuffer_to_vfbs(&vfb->base)->surface->res.backup;

	if (WARN_ON(!buf))
		return 0;

	return vmw_bo_unpin(dev_priv, buf, false);
}