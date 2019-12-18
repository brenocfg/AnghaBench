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
struct sk_buff {int len; int /*<<< orphan*/  cb; } ;
struct TYPE_2__ {int /*<<< orphan*/  tail_align; int /*<<< orphan*/  head_align; } ;
struct cfhsi {int aggregation_len; TYPE_1__ cfg; } ;
struct caif_payload_info {int hdr_len; } ;

/* Variables and functions */
 int PAD_POW2 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cfhsi_update_aggregation_stats(struct cfhsi *cfhsi,
					   const struct sk_buff *skb,
					   int direction)
{
	struct caif_payload_info *info;
	int hpad, tpad, len;

	info = (struct caif_payload_info *)&skb->cb;
	hpad = 1 + PAD_POW2((info->hdr_len + 1), cfhsi->cfg.head_align);
	tpad = PAD_POW2((skb->len + hpad), cfhsi->cfg.tail_align);
	len = skb->len + hpad + tpad;

	if (direction > 0)
		cfhsi->aggregation_len += len;
	else if (direction < 0)
		cfhsi->aggregation_len -= len;
}