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
struct rockchip_drm_private {int /*<<< orphan*/  psr_list_lock; int /*<<< orphan*/  psr_list; } ;
struct psr_drv {int inhibit_count; int enabled; int (* set ) (struct drm_encoder*,int) ;int /*<<< orphan*/  list; struct drm_encoder* encoder; int /*<<< orphan*/  lock; int /*<<< orphan*/  flush_work; } ;
struct drm_encoder {TYPE_1__* dev; } ;
struct TYPE_2__ {struct rockchip_drm_private* dev_private; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct psr_drv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psr_flush_handler ; 

int rockchip_drm_psr_register(struct drm_encoder *encoder,
			int (*psr_set)(struct drm_encoder *, bool enable))
{
	struct rockchip_drm_private *drm_drv;
	struct psr_drv *psr;

	if (!encoder || !psr_set)
		return -EINVAL;

	drm_drv = encoder->dev->dev_private;

	psr = kzalloc(sizeof(struct psr_drv), GFP_KERNEL);
	if (!psr)
		return -ENOMEM;

	INIT_DELAYED_WORK(&psr->flush_work, psr_flush_handler);
	mutex_init(&psr->lock);

	psr->inhibit_count = 1;
	psr->enabled = false;
	psr->encoder = encoder;
	psr->set = psr_set;

	mutex_lock(&drm_drv->psr_list_lock);
	list_add_tail(&psr->list, &drm_drv->psr_list);
	mutex_unlock(&drm_drv->psr_list_lock);

	return 0;
}