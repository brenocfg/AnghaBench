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
struct common_obj {TYPE_4__* next_frm; TYPE_4__* cur_frm; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  dma_queue; } ;
struct TYPE_6__ {int frm_fmt; } ;
struct TYPE_7__ {TYPE_1__ std_info; } ;
struct channel_obj {int field_id; scalar_t__ channel_id; TYPE_2__ vpifparams; struct common_obj* common; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_10__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_8__ {TYPE_5__ vb2_buf; } ;
struct TYPE_9__ {TYPE_3__ vb; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int VPIF_NUMOBJECTS ; 
 scalar_t__** channel_first_int ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_interlaced_mode (int,struct common_obj*) ; 
 int /*<<< orphan*/  process_progressive_mode (struct common_obj*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_buffer_done (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int vpif_channel_getfid (scalar_t__) ; 
 int /*<<< orphan*/  vpif_intr_status (int) ; 
 struct vpif_device vpif_obj ; 

__attribute__((used)) static irqreturn_t vpif_channel_isr(int irq, void *dev_id)
{
	struct vpif_device *dev = &vpif_obj;
	struct channel_obj *ch;
	struct common_obj *common;
	int fid = -1, i;
	int channel_id;

	channel_id = *(int *)(dev_id);
	if (!vpif_intr_status(channel_id + 2))
		return IRQ_NONE;

	ch = dev->dev[channel_id];
	for (i = 0; i < VPIF_NUMOBJECTS; i++) {
		common = &ch->common[i];
		/* If streaming is started in this channel */

		if (1 == ch->vpifparams.std_info.frm_fmt) {
			spin_lock(&common->irqlock);
			if (list_empty(&common->dma_queue)) {
				spin_unlock(&common->irqlock);
				continue;
			}
			spin_unlock(&common->irqlock);

			/* Progressive mode */
			if (!channel_first_int[i][channel_id]) {
				/* Mark status of the cur_frm to
				 * done and unlock semaphore on it */
				common->cur_frm->vb.vb2_buf.timestamp =
						ktime_get_ns();
				vb2_buffer_done(&common->cur_frm->vb.vb2_buf,
						VB2_BUF_STATE_DONE);
				/* Make cur_frm pointing to next_frm */
				common->cur_frm = common->next_frm;
			}

			channel_first_int[i][channel_id] = 0;
			process_progressive_mode(common);
		} else {
			/* Interlaced mode */
			/* If it is first interrupt, ignore it */

			if (channel_first_int[i][channel_id]) {
				channel_first_int[i][channel_id] = 0;
				continue;
			}

			if (0 == i) {
				ch->field_id ^= 1;
				/* Get field id from VPIF registers */
				fid = vpif_channel_getfid(ch->channel_id + 2);
				/* If fid does not match with stored field id */
				if (fid != ch->field_id) {
					/* Make them in sync */
					if (0 == fid)
						ch->field_id = fid;

					return IRQ_HANDLED;
				}
			}
			process_interlaced_mode(fid, common);
		}
	}

	return IRQ_HANDLED;
}