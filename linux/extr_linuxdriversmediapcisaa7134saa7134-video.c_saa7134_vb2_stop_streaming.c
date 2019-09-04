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
struct vb2_queue {struct saa7134_dmaqueue* drv_priv; } ;
struct saa7134_dmaqueue {struct saa7134_dev* dev; } ;
struct saa7134_dev {int /*<<< orphan*/  qos_request; int /*<<< orphan*/  video_vbq; struct saa7134_dmaqueue vbi_q; int /*<<< orphan*/  vbi_vbq; struct saa7134_dmaqueue video_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_qos_remove_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saa7134_stop_streaming (struct saa7134_dev*,struct saa7134_dmaqueue*) ; 
 int /*<<< orphan*/  vb2_is_streaming (int /*<<< orphan*/ *) ; 

void saa7134_vb2_stop_streaming(struct vb2_queue *vq)
{
	struct saa7134_dmaqueue *dmaq = vq->drv_priv;
	struct saa7134_dev *dev = dmaq->dev;

	saa7134_stop_streaming(dev, dmaq);

	if ((dmaq == &dev->video_q && !vb2_is_streaming(&dev->vbi_vbq)) ||
	    (dmaq == &dev->vbi_q && !vb2_is_streaming(&dev->video_vbq)))
		pm_qos_remove_request(&dev->qos_request);
}