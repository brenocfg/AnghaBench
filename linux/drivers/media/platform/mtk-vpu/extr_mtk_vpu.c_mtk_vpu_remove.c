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
struct platform_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ wq; } ;
struct mtk_vpu {int /*<<< orphan*/  clk; int /*<<< orphan*/  vpu_mutex; TYPE_1__ wdt; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_FW ; 
 int /*<<< orphan*/  P_FW ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  flush_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct mtk_vpu* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  vpu_debugfs ; 
 int /*<<< orphan*/  vpu_free_ext_mem (struct mtk_vpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_vpu_remove(struct platform_device *pdev)
{
	struct mtk_vpu *vpu = platform_get_drvdata(pdev);

#ifdef CONFIG_DEBUG_FS
	debugfs_remove(vpu_debugfs);
#endif
	if (vpu->wdt.wq) {
		flush_workqueue(vpu->wdt.wq);
		destroy_workqueue(vpu->wdt.wq);
	}
	vpu_free_ext_mem(vpu, P_FW);
	vpu_free_ext_mem(vpu, D_FW);
	mutex_destroy(&vpu->vpu_mutex);
	clk_unprepare(vpu->clk);

	return 0;
}