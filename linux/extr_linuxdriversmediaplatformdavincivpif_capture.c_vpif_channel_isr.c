#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vpif_device {struct channel_obj** dev; } ;
struct TYPE_8__ {scalar_t__ field; } ;
struct TYPE_9__ {TYPE_3__ pix; } ;
struct TYPE_10__ {TYPE_4__ fmt; } ;
struct common_obj {scalar_t__ cur_frm; scalar_t__ next_frm; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  dma_queue; TYPE_5__ fmt; } ;
struct TYPE_6__ {int frm_fmt; } ;
struct TYPE_7__ {TYPE_1__ std_info; } ;
struct channel_obj {int field_id; int /*<<< orphan*/  channel_id; TYPE_2__ vpifparams; struct common_obj* common; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ V4L2_FIELD_NONE ; 
 int VPIF_NUMBER_OF_OBJECTS ; 
 scalar_t__** channel_first_int ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int vpif_channel_getfid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpif_intr_status (int) ; 
 struct vpif_device vpif_obj ; 
 int /*<<< orphan*/  vpif_process_buffer_complete (struct common_obj*) ; 
 int /*<<< orphan*/  vpif_schedule_next_buffer (struct common_obj*) ; 

__attribute__((used)) static irqreturn_t vpif_channel_isr(int irq, void *dev_id)
{
	struct vpif_device *dev = &vpif_obj;
	struct common_obj *common;
	struct channel_obj *ch;
	int channel_id;
	int fid = -1, i;

	channel_id = *(int *)(dev_id);
	if (!vpif_intr_status(channel_id))
		return IRQ_NONE;

	ch = dev->dev[channel_id];

	for (i = 0; i < VPIF_NUMBER_OF_OBJECTS; i++) {
		common = &ch->common[i];
		/* skip If streaming is not started in this channel */
		/* Check the field format */
		if (1 == ch->vpifparams.std_info.frm_fmt ||
		    common->fmt.fmt.pix.field == V4L2_FIELD_NONE) {
			/* Progressive mode */
			spin_lock(&common->irqlock);
			if (list_empty(&common->dma_queue)) {
				spin_unlock(&common->irqlock);
				continue;
			}
			spin_unlock(&common->irqlock);

			if (!channel_first_int[i][channel_id])
				vpif_process_buffer_complete(common);

			channel_first_int[i][channel_id] = 0;

			vpif_schedule_next_buffer(common);


			channel_first_int[i][channel_id] = 0;
		} else {
			/**
			 * Interlaced mode. If it is first interrupt, ignore
			 * it
			 */
			if (channel_first_int[i][channel_id]) {
				channel_first_int[i][channel_id] = 0;
				continue;
			}
			if (0 == i) {
				ch->field_id ^= 1;
				/* Get field id from VPIF registers */
				fid = vpif_channel_getfid(ch->channel_id);
				if (fid != ch->field_id) {
					/**
					 * If field id does not match stored
					 * field id, make them in sync
					 */
					if (0 == fid)
						ch->field_id = fid;
					return IRQ_HANDLED;
				}
			}
			/* device field id and local field id are in sync */
			if (0 == fid) {
				/* this is even field */
				if (common->cur_frm == common->next_frm)
					continue;

				/* mark the current buffer as done */
				vpif_process_buffer_complete(common);
			} else if (1 == fid) {
				/* odd field */
				spin_lock(&common->irqlock);
				if (list_empty(&common->dma_queue) ||
				    (common->cur_frm != common->next_frm)) {
					spin_unlock(&common->irqlock);
					continue;
				}
				spin_unlock(&common->irqlock);

				vpif_schedule_next_buffer(common);
			}
		}
	}
	return IRQ_HANDLED;
}