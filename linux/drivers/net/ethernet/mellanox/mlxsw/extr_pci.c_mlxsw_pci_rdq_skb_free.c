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
struct sk_buff {int dummy; } ;
struct TYPE_3__ {struct sk_buff* skb; } ;
struct TYPE_4__ {TYPE_1__ rdq; } ;
struct mlxsw_pci_queue_elem_info {char* elem; TYPE_2__ u; } ;
struct mlxsw_pci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  mlxsw_pci_wqe_frag_unmap (struct mlxsw_pci*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_pci_rdq_skb_free(struct mlxsw_pci *mlxsw_pci,
				   struct mlxsw_pci_queue_elem_info *elem_info)
{
	struct sk_buff *skb;
	char *wqe;

	skb = elem_info->u.rdq.skb;
	wqe = elem_info->elem;

	mlxsw_pci_wqe_frag_unmap(mlxsw_pci, wqe, 0, DMA_FROM_DEVICE);
	dev_kfree_skb_any(skb);
}