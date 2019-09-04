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
struct usb_cardstate {int busy; int /*<<< orphan*/  bulk_out_urb; int /*<<< orphan*/  bulk_out_epnum; int /*<<< orphan*/  udev; int /*<<< orphan*/  bulk_out_size; } ;
struct cmdbuf_t {scalar_t__ len; scalar_t__ offset; scalar_t__ buf; scalar_t__ wake_tasklet; int /*<<< orphan*/ * prev; struct cmdbuf_t* next; } ;
struct TYPE_2__ {struct usb_cardstate* usb; } ;
struct cardstate {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; scalar_t__ connected; struct cmdbuf_t* cmdbuf; int /*<<< orphan*/  cmdlock; scalar_t__ curlen; int /*<<< orphan*/ * lastcmdbuf; int /*<<< orphan*/  cmdbytes; TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_OUTPUT ; 
 int ENODEV ; 
 int ENOENT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  gigaset_write_bulk_callback ; 
 int /*<<< orphan*/  kfree (struct cmdbuf_t*) ; 
 int min (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (scalar_t__) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,struct cardstate*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_cb(struct cardstate *cs)
{
	struct cmdbuf_t *cb = cs->cmdbuf;
	unsigned long flags;
	int count;
	int status = -ENOENT;
	struct usb_cardstate *ucs = cs->hw.usb;

	do {
		if (!cb->len) {
			spin_lock_irqsave(&cs->cmdlock, flags);
			cs->cmdbytes -= cs->curlen;
			gig_dbg(DEBUG_OUTPUT, "send_cb: sent %u bytes, %u left",
				cs->curlen, cs->cmdbytes);
			cs->cmdbuf = cb->next;
			if (cs->cmdbuf) {
				cs->cmdbuf->prev = NULL;
				cs->curlen = cs->cmdbuf->len;
			} else {
				cs->lastcmdbuf = NULL;
				cs->curlen = 0;
			}
			spin_unlock_irqrestore(&cs->cmdlock, flags);

			if (cb->wake_tasklet)
				tasklet_schedule(cb->wake_tasklet);
			kfree(cb);

			cb = cs->cmdbuf;
		}

		if (cb) {
			count = min(cb->len, ucs->bulk_out_size);
			gig_dbg(DEBUG_OUTPUT, "send_cb: send %d bytes", count);

			usb_fill_bulk_urb(ucs->bulk_out_urb, ucs->udev,
					  usb_sndbulkpipe(ucs->udev,
							  ucs->bulk_out_epnum),
					  cb->buf + cb->offset, count,
					  gigaset_write_bulk_callback, cs);

			cb->offset += count;
			cb->len -= count;
			ucs->busy = 1;

			spin_lock_irqsave(&cs->lock, flags);
			status = cs->connected ?
				usb_submit_urb(ucs->bulk_out_urb, GFP_ATOMIC) :
				-ENODEV;
			spin_unlock_irqrestore(&cs->lock, flags);

			if (status) {
				ucs->busy = 0;
				dev_err(cs->dev,
					"could not submit urb (error %d)\n",
					-status);
				cb->len = 0; /* skip urb => remove cb+wakeup
						in next loop cycle */
			}
		}
	} while (cb && status); /* next command on error */

	return status;
}