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
struct vpu_wdt_handler {void (* reset_func ) (void*) ;void* priv; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct vpu_wdt_handler* handler; } ;
struct mtk_vpu {int /*<<< orphan*/ * dev; int /*<<< orphan*/  vpu_mutex; TYPE_1__ wdt; } ;
typedef  enum rst_id { ____Placeholder_rst_id } rst_id ;

/* Variables and functions */
 int EINVAL ; 
 int EPROBE_DEFER ; 
 int VPU_RST_MAX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mtk_vpu* platform_get_drvdata (struct platform_device*) ; 

int vpu_wdt_reg_handler(struct platform_device *pdev,
			void wdt_reset(void *),
			void *priv, enum rst_id id)
{
	struct mtk_vpu *vpu = platform_get_drvdata(pdev);
	struct vpu_wdt_handler *handler;

	if (!vpu) {
		dev_err(&pdev->dev, "vpu device in not ready\n");
		return -EPROBE_DEFER;
	}

	handler = vpu->wdt.handler;

	if (id >= 0 && id < VPU_RST_MAX && wdt_reset) {
		dev_dbg(vpu->dev, "wdt register id %d\n", id);
		mutex_lock(&vpu->vpu_mutex);
		handler[id].reset_func = wdt_reset;
		handler[id].priv = priv;
		mutex_unlock(&vpu->vpu_mutex);
		return 0;
	}

	dev_err(vpu->dev, "register vpu wdt handler failed\n");
	return -EINVAL;
}