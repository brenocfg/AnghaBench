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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  mbox_len; } ;
struct nfp_net {TYPE_1__ tlv_caps; } ;

/* Variables and functions */
 scalar_t__ NFP_NET_CFG_MBOX_SIMPLE_VAL ; 
 scalar_t__ round_down (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 nfp_ccm_mbox_max_msg(struct nfp_net *nn)
{
	return round_down(nn->tlv_caps.mbox_len, 4) -
		NFP_NET_CFG_MBOX_SIMPLE_VAL - /* common mbox command header */
		4 * 2; /* Msg TLV plus End TLV headers */
}