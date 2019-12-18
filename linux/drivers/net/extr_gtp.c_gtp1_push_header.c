#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; } ;
struct TYPE_3__ {int /*<<< orphan*/  o_tei; } ;
struct TYPE_4__ {TYPE_1__ v1; } ;
struct pdp_ctx {TYPE_2__ u; } ;
struct gtp1_header {int flags; int /*<<< orphan*/  tid; int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GTP_TPDU ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 struct gtp1_header* skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static inline void gtp1_push_header(struct sk_buff *skb, struct pdp_ctx *pctx)
{
	int payload_len = skb->len;
	struct gtp1_header *gtp1;

	gtp1 = skb_push(skb, sizeof(*gtp1));

	/* Bits    8  7  6  5  4  3  2	1
	 *	  +--+--+--+--+--+--+--+--+
	 *	  |version |PT| 0| E| S|PN|
	 *	  +--+--+--+--+--+--+--+--+
	 *	    0  0  1  1	1  0  0  0
	 */
	gtp1->flags	= 0x30; /* v1, GTP-non-prime. */
	gtp1->type	= GTP_TPDU;
	gtp1->length	= htons(payload_len);
	gtp1->tid	= htonl(pctx->u.v1.o_tei);

	/* TODO: Suppport for extension header, sequence number and N-PDU.
	 *	 Update the length field if any of them is available.
	 */
}