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
struct work_request_hdr {int /*<<< orphan*/  wr_hi; } ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;

/* Variables and functions */
 unsigned long FW_CRYPTO_LOOKASIDE_WR ; 
 unsigned long FW_WR_OP_G (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_IMM_TX_PKT_LEN ; 
 scalar_t__ SGE_MAX_WR_LEN ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int is_ofld_imm(const struct sk_buff *skb)
{
	struct work_request_hdr *req = (struct work_request_hdr *)skb->data;
	unsigned long opcode = FW_WR_OP_G(ntohl(req->wr_hi));

	if (opcode == FW_CRYPTO_LOOKASIDE_WR)
		return skb->len <= SGE_MAX_WR_LEN;
	else
		return skb->len <= MAX_IMM_TX_PKT_LEN;
}