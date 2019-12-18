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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct fc_frame_header {int dummy; } ;
struct fc_frame {int dummy; } ;

/* Variables and functions */
 scalar_t__ FC_FRAME_HEADROOM ; 
 scalar_t__ FC_FRAME_TAILROOM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ NET_SKB_PAD ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct sk_buff* alloc_skb_fclone (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_frame_init (struct fc_frame*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

struct fc_frame *_fc_frame_alloc(size_t len)
{
	struct fc_frame *fp;
	struct sk_buff *skb;

	WARN_ON((len % sizeof(u32)) != 0);
	len += sizeof(struct fc_frame_header);
	skb = alloc_skb_fclone(len + FC_FRAME_HEADROOM + FC_FRAME_TAILROOM +
			       NET_SKB_PAD, GFP_ATOMIC);
	if (!skb)
		return NULL;
	skb_reserve(skb, NET_SKB_PAD + FC_FRAME_HEADROOM);
	fp = (struct fc_frame *) skb;
	fc_frame_init(fp);
	skb_put(skb, len);
	return fp;
}