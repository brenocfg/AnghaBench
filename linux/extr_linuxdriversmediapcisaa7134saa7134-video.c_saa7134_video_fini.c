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
struct TYPE_4__ {int /*<<< orphan*/  pt; } ;
struct TYPE_3__ {int /*<<< orphan*/  pt; } ;
struct saa7134_dev {int /*<<< orphan*/  radio_ctrl_handler; int /*<<< orphan*/  ctrl_handler; TYPE_2__ vbi_q; int /*<<< orphan*/  pci; int /*<<< orphan*/  vbi_vbq; TYPE_1__ video_q; int /*<<< orphan*/  video_vbq; } ;

/* Variables and functions */
 scalar_t__ card_has_radio (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa7134_pgtable_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_queue_release (int /*<<< orphan*/ *) ; 

void saa7134_video_fini(struct saa7134_dev *dev)
{
	/* free stuff */
	vb2_queue_release(&dev->video_vbq);
	saa7134_pgtable_free(dev->pci, &dev->video_q.pt);
	vb2_queue_release(&dev->vbi_vbq);
	saa7134_pgtable_free(dev->pci, &dev->vbi_q.pt);
	v4l2_ctrl_handler_free(&dev->ctrl_handler);
	if (card_has_radio(dev))
		v4l2_ctrl_handler_free(&dev->radio_ctrl_handler);
}