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
struct s5p_mfc_dev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  vfd_dec; int /*<<< orphan*/  vfd_enc; int /*<<< orphan*/  watchdog_work; int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  mfc_mutex; struct s5p_mfc_ctx** ctx; } ;
struct s5p_mfc_ctx {int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int MFC_NUM_CONTEXTS ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct s5p_mfc_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  s5p_mfc_final_pm (struct s5p_mfc_dev*) ; 
 int /*<<< orphan*/  s5p_mfc_unconfigure_dma_memory (struct s5p_mfc_dev*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_device_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_mfc_remove(struct platform_device *pdev)
{
	struct s5p_mfc_dev *dev = platform_get_drvdata(pdev);
	struct s5p_mfc_ctx *ctx;
	int i;

	v4l2_info(&dev->v4l2_dev, "Removing %s\n", pdev->name);

	/*
	 * Clear ctx dev pointer to avoid races between s5p_mfc_remove()
	 * and s5p_mfc_release() and s5p_mfc_release() accessing ctx->dev
	 * after s5p_mfc_remove() is run during unbind.
	*/
	mutex_lock(&dev->mfc_mutex);
	for (i = 0; i < MFC_NUM_CONTEXTS; i++) {
		ctx = dev->ctx[i];
		if (!ctx)
			continue;
		/* clear ctx->dev */
		ctx->dev = NULL;
	}
	mutex_unlock(&dev->mfc_mutex);

	del_timer_sync(&dev->watchdog_timer);
	flush_work(&dev->watchdog_work);

	video_unregister_device(dev->vfd_enc);
	video_unregister_device(dev->vfd_dec);
	video_device_release(dev->vfd_enc);
	video_device_release(dev->vfd_dec);
	v4l2_device_unregister(&dev->v4l2_dev);
	s5p_mfc_unconfigure_dma_memory(dev);

	s5p_mfc_final_pm(dev);
	return 0;
}