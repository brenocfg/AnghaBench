#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct omap_vout_device {int field_id; TYPE_2__* next_frm; TYPE_2__* cur_frm; int /*<<< orphan*/  dma_queue; int /*<<< orphan*/  sequence; scalar_t__ first_int; } ;
struct TYPE_6__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_4__ {TYPE_3__ vb2_buf; scalar_t__ sequence; } ;
struct TYPE_5__ {TYPE_1__ vbuf; } ;

/* Variables and functions */
 unsigned int DISPC_IRQ_EVSYNC_EVEN ; 
 unsigned int DISPC_IRQ_EVSYNC_ODD ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_buffer_done (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omapvid_handle_interlace_display(struct omap_vout_device *vout,
		unsigned int irqstatus, u64 ts)
{
	u32 fid;

	if (vout->first_int) {
		vout->first_int = 0;
		goto err;
	}

	if (irqstatus & DISPC_IRQ_EVSYNC_ODD)
		fid = 1;
	else if (irqstatus & DISPC_IRQ_EVSYNC_EVEN)
		fid = 0;
	else
		goto err;

	vout->field_id ^= 1;
	if (fid != vout->field_id) {
		if (fid == 0)
			vout->field_id = fid;
	} else if (0 == fid) {
		if (vout->cur_frm == vout->next_frm)
			goto err;

		vout->cur_frm->vbuf.vb2_buf.timestamp = ts;
		vout->cur_frm->vbuf.sequence = vout->sequence++;
		vb2_buffer_done(&vout->cur_frm->vbuf.vb2_buf, VB2_BUF_STATE_DONE);
		vout->cur_frm = vout->next_frm;
	} else {
		if (list_empty(&vout->dma_queue) ||
				(vout->cur_frm != vout->next_frm))
			goto err;
	}

	return vout->field_id;
err:
	return 0;
}