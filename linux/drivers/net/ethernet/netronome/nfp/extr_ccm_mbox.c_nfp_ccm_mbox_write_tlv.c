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
struct nfp_net {int dummy; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFP_NET_MBOX_TLV_LEN ; 
 int /*<<< orphan*/  NFP_NET_MBOX_TLV_TYPE ; 
 int /*<<< orphan*/  nn_writel (struct nfp_net*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nfp_ccm_mbox_write_tlv(struct nfp_net *nn, u32 off, u32 type, u32 len)
{
	nn_writel(nn, off,
		  FIELD_PREP(NFP_NET_MBOX_TLV_TYPE, type) |
		  FIELD_PREP(NFP_NET_MBOX_TLV_LEN, len));
}