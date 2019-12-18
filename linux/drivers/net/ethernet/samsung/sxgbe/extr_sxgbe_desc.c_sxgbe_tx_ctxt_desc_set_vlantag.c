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
struct sxgbe_tx_ctxt_desc {int vltag_valid; int vlan_tag; } ;

/* Variables and functions */

__attribute__((used)) static void sxgbe_tx_ctxt_desc_set_vlantag(struct sxgbe_tx_ctxt_desc *p,
					   int is_vlanvalid, int vlan_tag)
{
	if (is_vlanvalid) {
		p->vltag_valid = is_vlanvalid;
		p->vlan_tag = vlan_tag;
	}
}