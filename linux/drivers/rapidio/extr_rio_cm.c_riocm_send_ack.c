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
struct rio_channel {int /*<<< orphan*/  rdev; int /*<<< orphan*/  id; int /*<<< orphan*/  cmdev; int /*<<< orphan*/  rem_channel; int /*<<< orphan*/  rem_destid; int /*<<< orphan*/  loc_destid; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; void* dst_mbox; void* src_mbox; void* dst_id; void* src_id; } ;
struct rio_ch_chan_hdr {int /*<<< orphan*/  ch_op; TYPE_1__ bhdr; void* src_ch; void* dst_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_CONN_ACK ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RIO_CM_CHAN ; 
 void* cmbox ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rio_ch_chan_hdr*) ; 
 struct rio_ch_chan_hdr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rio_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  riocm_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int riocm_post_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rio_ch_chan_hdr*,int) ; 
 int /*<<< orphan*/  riocm_queue_req (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rio_ch_chan_hdr*,int) ; 

__attribute__((used)) static int riocm_send_ack(struct rio_channel *ch)
{
	struct rio_ch_chan_hdr *hdr;
	int ret;

	hdr = kzalloc(sizeof(*hdr), GFP_KERNEL);
	if (hdr == NULL)
		return -ENOMEM;

	hdr->bhdr.src_id = htonl(ch->loc_destid);
	hdr->bhdr.dst_id = htonl(ch->rem_destid);
	hdr->dst_ch = htons(ch->rem_channel);
	hdr->src_ch = htons(ch->id);
	hdr->bhdr.src_mbox = cmbox;
	hdr->bhdr.dst_mbox = cmbox;
	hdr->bhdr.type = RIO_CM_CHAN;
	hdr->ch_op = CM_CONN_ACK;

	/* ATTN: the function call below relies on the fact that underlying
	 * add_outb_message() routine copies TX data into its internal transfer
	 * buffer. Review if switching to direct buffer version.
	 */
	ret = riocm_post_send(ch->cmdev, ch->rdev, hdr, sizeof(*hdr));

	if (ret == -EBUSY && !riocm_queue_req(ch->cmdev,
					      ch->rdev, hdr, sizeof(*hdr)))
		return 0;
	kfree(hdr);

	if (ret)
		riocm_error("send ACK to ch_%d on %s failed (ret=%d)",
			    ch->id, rio_name(ch->rdev), ret);
	return ret;
}