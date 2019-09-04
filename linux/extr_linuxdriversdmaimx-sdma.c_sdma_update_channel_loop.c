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
struct TYPE_5__ {int /*<<< orphan*/  tx; } ;
struct sdma_desc {size_t buf_tail; size_t buf_ptail; int num_bd; TYPE_2__ vd; int /*<<< orphan*/  period_len; int /*<<< orphan*/  chn_real_count; struct sdma_buffer_descriptor* bd; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct sdma_channel {int status; TYPE_3__ vc; struct sdma_desc* desc; } ;
struct TYPE_4__ {int status; int /*<<< orphan*/  count; } ;
struct sdma_buffer_descriptor {TYPE_1__ mode; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;

/* Variables and functions */
 int BD_DONE ; 
 int BD_RROR ; 
 int DMA_ERROR ; 
 int EIO ; 
 int /*<<< orphan*/  dmaengine_desc_get_callback_invoke (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sdma_update_channel_loop(struct sdma_channel *sdmac)
{
	struct sdma_buffer_descriptor *bd;
	int error = 0;
	enum dma_status	old_status = sdmac->status;

	/*
	 * loop mode. Iterate over descriptors, re-setup them and
	 * call callback function.
	 */
	while (sdmac->desc) {
		struct sdma_desc *desc = sdmac->desc;

		bd = &desc->bd[desc->buf_tail];

		if (bd->mode.status & BD_DONE)
			break;

		if (bd->mode.status & BD_RROR) {
			bd->mode.status &= ~BD_RROR;
			sdmac->status = DMA_ERROR;
			error = -EIO;
		}

	       /*
		* We use bd->mode.count to calculate the residue, since contains
		* the number of bytes present in the current buffer descriptor.
		*/

		desc->chn_real_count = bd->mode.count;
		bd->mode.status |= BD_DONE;
		bd->mode.count = desc->period_len;
		desc->buf_ptail = desc->buf_tail;
		desc->buf_tail = (desc->buf_tail + 1) % desc->num_bd;

		/*
		 * The callback is called from the interrupt context in order
		 * to reduce latency and to avoid the risk of altering the
		 * SDMA transaction status by the time the client tasklet is
		 * executed.
		 */
		spin_unlock(&sdmac->vc.lock);
		dmaengine_desc_get_callback_invoke(&desc->vd.tx, NULL);
		spin_lock(&sdmac->vc.lock);

		if (error)
			sdmac->status = old_status;
	}
}