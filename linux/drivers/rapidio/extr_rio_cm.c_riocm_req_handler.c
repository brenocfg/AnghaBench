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
typedef  void* u16 ;
struct rio_channel {scalar_t__ state; int /*<<< orphan*/  comp; int /*<<< orphan*/  lock; int /*<<< orphan*/  accept_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  src_id; } ;
struct rio_ch_chan_hdr {int /*<<< orphan*/  src_ch; TYPE_1__ bhdr; int /*<<< orphan*/  dst_ch; } ;
struct conn_req {int /*<<< orphan*/  node; struct cm_dev* cmdev; void* chan; int /*<<< orphan*/  destid; } ;
struct cm_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ RIO_CM_LISTEN ; 
 int /*<<< orphan*/  RX_CMD ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct conn_req* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  riocm_debug (int /*<<< orphan*/ ,char*,void*) ; 
 struct rio_channel* riocm_get_channel (void*) ; 
 int /*<<< orphan*/  riocm_put_channel (struct rio_channel*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int riocm_req_handler(struct cm_dev *cm, void *req_data)
{
	struct rio_channel *ch;
	struct conn_req *req;
	struct rio_ch_chan_hdr *hh = req_data;
	u16 chnum;

	chnum = ntohs(hh->dst_ch);

	ch = riocm_get_channel(chnum);

	if (!ch)
		return -ENODEV;

	if (ch->state != RIO_CM_LISTEN) {
		riocm_debug(RX_CMD, "channel %d is not in listen state", chnum);
		riocm_put_channel(ch);
		return -EINVAL;
	}

	req = kzalloc(sizeof(*req), GFP_KERNEL);
	if (!req) {
		riocm_put_channel(ch);
		return -ENOMEM;
	}

	req->destid = ntohl(hh->bhdr.src_id);
	req->chan = ntohs(hh->src_ch);
	req->cmdev = cm;

	spin_lock_bh(&ch->lock);
	list_add_tail(&req->node, &ch->accept_queue);
	spin_unlock_bh(&ch->lock);
	complete(&ch->comp);
	riocm_put_channel(ch);

	return 0;
}