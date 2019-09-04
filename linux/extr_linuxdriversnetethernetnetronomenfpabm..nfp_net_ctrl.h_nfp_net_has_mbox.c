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
struct nfp_net_tlv_caps {scalar_t__ mbox_len; } ;

/* Variables and functions */
 scalar_t__ NFP_NET_CFG_MBOX_SIMPLE_LEN ; 

__attribute__((used)) static inline bool nfp_net_has_mbox(struct nfp_net_tlv_caps *caps)
{
	return caps->mbox_len >= NFP_NET_CFG_MBOX_SIMPLE_LEN;
}