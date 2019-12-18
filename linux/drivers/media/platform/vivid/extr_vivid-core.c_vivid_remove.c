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
struct TYPE_2__ {int /*<<< orphan*/  node; } ;
struct vivid_dev {int /*<<< orphan*/  v4l2_dev; scalar_t__ cec_workqueue; int /*<<< orphan*/ * cec_tx_adap; int /*<<< orphan*/  cec_rx_adap; TYPE_1__ fb_info; scalar_t__ has_fb; int /*<<< orphan*/  radio_tx_dev; scalar_t__ has_radio_tx; int /*<<< orphan*/  radio_rx_dev; scalar_t__ has_radio_rx; int /*<<< orphan*/  sdr_cap_dev; scalar_t__ has_sdr_cap; int /*<<< orphan*/  vbi_out_dev; scalar_t__ has_vbi_out; int /*<<< orphan*/  vbi_cap_dev; scalar_t__ has_vbi_cap; int /*<<< orphan*/  vid_out_dev; scalar_t__ has_vid_out; int /*<<< orphan*/  vid_cap_dev; scalar_t__ has_vid_cap; int /*<<< orphan*/  mdev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 unsigned int MAX_OUTPUTS ; 
 int /*<<< orphan*/  cec_unregister_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  media_device_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_device_unregister (int /*<<< orphan*/ *) ; 
 unsigned int n_devs ; 
 int /*<<< orphan*/  unregister_framebuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_device_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_device_node_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vivid_cec_bus_free_work (struct vivid_dev*) ; 
 struct vivid_dev** vivid_devs ; 
 int /*<<< orphan*/  vivid_fb_release_buffers (struct vivid_dev*) ; 

__attribute__((used)) static int vivid_remove(struct platform_device *pdev)
{
	struct vivid_dev *dev;
	unsigned int i, j;

	for (i = 0; i < n_devs; i++) {
		dev = vivid_devs[i];
		if (!dev)
			continue;

#ifdef CONFIG_MEDIA_CONTROLLER
		media_device_unregister(&dev->mdev);
		media_device_cleanup(&dev->mdev);
#endif

		if (dev->has_vid_cap) {
			v4l2_info(&dev->v4l2_dev, "unregistering %s\n",
				video_device_node_name(&dev->vid_cap_dev));
			video_unregister_device(&dev->vid_cap_dev);
		}
		if (dev->has_vid_out) {
			v4l2_info(&dev->v4l2_dev, "unregistering %s\n",
				video_device_node_name(&dev->vid_out_dev));
			video_unregister_device(&dev->vid_out_dev);
		}
		if (dev->has_vbi_cap) {
			v4l2_info(&dev->v4l2_dev, "unregistering %s\n",
				video_device_node_name(&dev->vbi_cap_dev));
			video_unregister_device(&dev->vbi_cap_dev);
		}
		if (dev->has_vbi_out) {
			v4l2_info(&dev->v4l2_dev, "unregistering %s\n",
				video_device_node_name(&dev->vbi_out_dev));
			video_unregister_device(&dev->vbi_out_dev);
		}
		if (dev->has_sdr_cap) {
			v4l2_info(&dev->v4l2_dev, "unregistering %s\n",
				video_device_node_name(&dev->sdr_cap_dev));
			video_unregister_device(&dev->sdr_cap_dev);
		}
		if (dev->has_radio_rx) {
			v4l2_info(&dev->v4l2_dev, "unregistering %s\n",
				video_device_node_name(&dev->radio_rx_dev));
			video_unregister_device(&dev->radio_rx_dev);
		}
		if (dev->has_radio_tx) {
			v4l2_info(&dev->v4l2_dev, "unregistering %s\n",
				video_device_node_name(&dev->radio_tx_dev));
			video_unregister_device(&dev->radio_tx_dev);
		}
		if (dev->has_fb) {
			v4l2_info(&dev->v4l2_dev, "unregistering fb%d\n",
				dev->fb_info.node);
			unregister_framebuffer(&dev->fb_info);
			vivid_fb_release_buffers(dev);
		}
		cec_unregister_adapter(dev->cec_rx_adap);
		for (j = 0; j < MAX_OUTPUTS; j++)
			cec_unregister_adapter(dev->cec_tx_adap[j]);
		if (dev->cec_workqueue) {
			vivid_cec_bus_free_work(dev);
			destroy_workqueue(dev->cec_workqueue);
		}
		v4l2_device_put(&dev->v4l2_dev);
		vivid_devs[i] = NULL;
	}
	return 0;
}