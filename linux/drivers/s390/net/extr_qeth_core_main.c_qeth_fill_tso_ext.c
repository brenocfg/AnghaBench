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
struct sk_buff {int dummy; } ;
struct qeth_hdr_ext_tso {int hdr_tot_len; int imb_hdr_no; int hdr_type; int hdr_version; int hdr_len; unsigned int payload_len; unsigned int dg_hdr_len; int /*<<< orphan*/  mss; } ;
struct qeth_hdr_tso {struct qeth_hdr_ext_tso ext; } ;
struct TYPE_2__ {int /*<<< orphan*/  gso_size; } ;

/* Variables and functions */
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void qeth_fill_tso_ext(struct qeth_hdr_tso *hdr,
			      unsigned int payload_len, struct sk_buff *skb,
			      unsigned int proto_len)
{
	struct qeth_hdr_ext_tso *ext = &hdr->ext;

	ext->hdr_tot_len = sizeof(*ext);
	ext->imb_hdr_no = 1;
	ext->hdr_type = 1;
	ext->hdr_version = 1;
	ext->hdr_len = 28;
	ext->payload_len = payload_len;
	ext->mss = skb_shinfo(skb)->gso_size;
	ext->dg_hdr_len = proto_len;
}