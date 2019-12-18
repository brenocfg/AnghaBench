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
struct qeth_hdr_layer3 {int ext_flags; scalar_t__ vlan_id; } ;

/* Variables and functions */
 int QETH_HDR_EXT_VLAN_FRAME ; 

__attribute__((used)) static inline bool qeth_l3_iqd_same_vlan(struct qeth_hdr_layer3 *h1,
					 struct qeth_hdr_layer3 *h2)
{
	return !((h1->ext_flags ^ h2->ext_flags) & QETH_HDR_EXT_VLAN_FRAME) &&
	       h1->vlan_id == h2->vlan_id;
}