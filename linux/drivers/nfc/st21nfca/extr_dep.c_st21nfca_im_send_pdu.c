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
struct TYPE_2__ {int /*<<< orphan*/  tx_work; struct sk_buff* tx_pending; } ;
struct st21nfca_hci_info {TYPE_1__ dep_info; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void st21nfca_im_send_pdu(struct st21nfca_hci_info *info,
						struct sk_buff *skb)
{
	info->dep_info.tx_pending = skb;
	schedule_work(&info->dep_info.tx_work);
}