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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  port_id; } ;
struct TYPE_4__ {TYPE_1__ port_info; } ;
struct metadata_dst {scalar_t__ type; TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ METADATA_HW_PORT_MUX ; 
 struct metadata_dst* skb_metadata_dst (struct sk_buff*) ; 

__attribute__((used)) static u16 bnxt_xmit_get_cfa_action(struct sk_buff *skb)
{
	struct metadata_dst *md_dst = skb_metadata_dst(skb);

	if (!md_dst || md_dst->type != METADATA_HW_PORT_MUX)
		return 0;

	return md_dst->u.port_info.port_id;
}