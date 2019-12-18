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
struct s5p_jpeg {int /*<<< orphan*/ * clocks; TYPE_1__* variant; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  vfd_encoder; int /*<<< orphan*/  vfd_decoder; int /*<<< orphan*/  dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int num_clocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct s5p_jpeg* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_status_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_dma_contig_clear_max_seg_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_jpeg_remove(struct platform_device *pdev)
{
	struct s5p_jpeg *jpeg = platform_get_drvdata(pdev);
	int i;

	pm_runtime_disable(jpeg->dev);

	video_unregister_device(jpeg->vfd_decoder);
	video_unregister_device(jpeg->vfd_encoder);
	vb2_dma_contig_clear_max_seg_size(&pdev->dev);
	v4l2_m2m_release(jpeg->m2m_dev);
	v4l2_device_unregister(&jpeg->v4l2_dev);

	if (!pm_runtime_status_suspended(&pdev->dev)) {
		for (i = jpeg->variant->num_clocks - 1; i >= 0; i--)
			clk_disable_unprepare(jpeg->clocks[i]);
	}

	return 0;
}