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
struct pvr2_stream {int /*<<< orphan*/  mutex; int /*<<< orphan*/  endpoint; int /*<<< orphan*/  dev; } ;
struct pvr2_buffer {int max_count; int id; int /*<<< orphan*/  purb; scalar_t__ ptr; int /*<<< orphan*/  status; struct pvr2_stream* stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  buffer_complete ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvr2_buffer_set_queued (struct pvr2_buffer*) ; 
 int /*<<< orphan*/  pvr2_buffer_wipe (struct pvr2_buffer*) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,struct pvr2_buffer*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pvr2_buffer_queue(struct pvr2_buffer *bp)
{
#undef SEED_BUFFER
#ifdef SEED_BUFFER
	unsigned int idx;
	unsigned int val;
#endif
	int ret = 0;
	struct pvr2_stream *sp;
	if (!bp) return -EINVAL;
	sp = bp->stream;
	mutex_lock(&sp->mutex);
	do {
		pvr2_buffer_wipe(bp);
		if (!sp->dev) {
			ret = -EIO;
			break;
		}
		pvr2_buffer_set_queued(bp);
#ifdef SEED_BUFFER
		for (idx = 0; idx < (bp->max_count) / 4; idx++) {
			val = bp->id << 24;
			val |= idx;
			((unsigned int *)(bp->ptr))[idx] = val;
		}
#endif
		bp->status = -EINPROGRESS;
		usb_fill_bulk_urb(bp->purb,      // struct urb *urb
				  sp->dev,       // struct usb_device *dev
				  // endpoint (below)
				  usb_rcvbulkpipe(sp->dev, sp->endpoint),
				  bp->ptr,       // void *transfer_buffer
				  bp->max_count, // int buffer_length
				  buffer_complete,
				  bp);
		usb_submit_urb(bp->purb, GFP_KERNEL);
	} while (0);
	mutex_unlock(&sp->mutex);
	return ret;
}