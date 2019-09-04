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
struct nfp_net_tlv_caps {int me_freq_mhz; int /*<<< orphan*/  mbox_len; int /*<<< orphan*/  mbox_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_NET_CFG_MBOX_BASE ; 
 int /*<<< orphan*/  NFP_NET_CFG_MBOX_VAL_MAX_SZ ; 
 int /*<<< orphan*/  memset (struct nfp_net_tlv_caps*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nfp_net_tlv_caps_reset(struct nfp_net_tlv_caps *caps)
{
	memset(caps, 0, sizeof(*caps));
	caps->me_freq_mhz = 1200;
	caps->mbox_off = NFP_NET_CFG_MBOX_BASE;
	caps->mbox_len = NFP_NET_CFG_MBOX_VAL_MAX_SZ;
}