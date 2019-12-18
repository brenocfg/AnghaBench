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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* recv ) (struct port_info*,struct sk_buff*) ;} ;
struct port_info {TYPE_1__ iscsic; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxgb3_arp_process (struct port_info*,struct sk_buff*) ; 
 scalar_t__ is_arp (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct port_info*,struct sk_buff*) ; 

__attribute__((used)) static void cxgb3_process_iscsi_prov_pack(struct port_info *pi,
					struct sk_buff *skb)
{
	if (is_arp(skb)) {
		cxgb3_arp_process(pi, skb);
		return;
	}

	if (pi->iscsic.recv)
		pi->iscsic.recv(pi, skb);

}