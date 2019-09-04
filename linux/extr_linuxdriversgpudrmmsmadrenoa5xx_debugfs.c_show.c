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
struct seq_file {scalar_t__ private; } ;
struct msm_drm_private {struct msm_gpu* gpu; } ;
struct drm_printer {int dummy; } ;
struct drm_info_node {TYPE_2__* info_ent; TYPE_1__* minor; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;
struct TYPE_4__ {int (* data ) (struct msm_gpu*,struct drm_printer*) ;} ;
struct TYPE_3__ {struct drm_device* dev; } ;

/* Variables and functions */
 struct drm_printer drm_seq_file_printer (struct seq_file*) ; 

__attribute__((used)) static int show(struct seq_file *m, void *arg)
{
	struct drm_info_node *node = (struct drm_info_node *) m->private;
	struct drm_device *dev = node->minor->dev;
	struct msm_drm_private *priv = dev->dev_private;
	struct drm_printer p = drm_seq_file_printer(m);
	int (*show)(struct msm_gpu *gpu, struct drm_printer *p) =
		node->info_ent->data;

	return show(priv->gpu, &p);
}