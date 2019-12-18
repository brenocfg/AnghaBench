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
struct platform_device {int /*<<< orphan*/  name; } ;
struct hantro_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  clocks; TYPE_1__* variant; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  mdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_clocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_bulk_unprepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hantro_remove_dec_func (struct hantro_dev*) ; 
 int /*<<< orphan*/  hantro_remove_enc_func (struct hantro_dev*) ; 
 int /*<<< orphan*/  media_device_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_device_unregister (int /*<<< orphan*/ *) ; 
 struct hantro_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hantro_remove(struct platform_device *pdev)
{
	struct hantro_dev *vpu = platform_get_drvdata(pdev);

	v4l2_info(&vpu->v4l2_dev, "Removing %s\n", pdev->name);

	media_device_unregister(&vpu->mdev);
	hantro_remove_dec_func(vpu);
	hantro_remove_enc_func(vpu);
	media_device_cleanup(&vpu->mdev);
	v4l2_m2m_release(vpu->m2m_dev);
	v4l2_device_unregister(&vpu->v4l2_dev);
	clk_bulk_unprepare(vpu->variant->num_clocks, vpu->clocks);
	pm_runtime_dont_use_autosuspend(vpu->dev);
	pm_runtime_disable(vpu->dev);
	return 0;
}