#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct soc_camera_host {TYPE_1__ v4l2_dev; struct sh_mobile_ceu_dev* priv; } ;
struct sh_mobile_ceu_dev {int /*<<< orphan*/  lock; TYPE_3__* active; } ;
struct TYPE_6__ {int /*<<< orphan*/  vb2_buf; } ;
struct TYPE_5__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEIER ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  ceu_write (struct sh_mobile_ceu_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_mobile_ceu_soft_reset (struct sh_mobile_ceu_dev*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 TYPE_2__* to_ceu_vb (TYPE_3__*) ; 
 int /*<<< orphan*/  vb2_buffer_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_mobile_ceu_clock_stop(struct soc_camera_host *ici)
{
	struct sh_mobile_ceu_dev *pcdev = ici->priv;

	/* disable capture, disable interrupts */
	ceu_write(pcdev, CEIER, 0);
	sh_mobile_ceu_soft_reset(pcdev);

	/* make sure active buffer is canceled */
	spin_lock_irq(&pcdev->lock);
	if (pcdev->active) {
		list_del_init(&to_ceu_vb(pcdev->active)->queue);
		vb2_buffer_done(&pcdev->active->vb2_buf, VB2_BUF_STATE_ERROR);
		pcdev->active = NULL;
	}
	spin_unlock_irq(&pcdev->lock);

	pm_runtime_put(ici->v4l2_dev.dev);
}