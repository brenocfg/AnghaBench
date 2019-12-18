#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  sys_port; int /*<<< orphan*/  lag_id; } ;
struct mlxsw_rx_info {int is_lag; int /*<<< orphan*/  trap_id; TYPE_3__ u; int /*<<< orphan*/  lag_port_index; } ;
struct TYPE_4__ {struct sk_buff* skb; } ;
struct TYPE_5__ {TYPE_1__ sdq; } ;
struct mlxsw_pci_queue_elem_info {char* elem; TYPE_2__ u; } ;
struct mlxsw_pci_queue {int /*<<< orphan*/  producer_counter; int /*<<< orphan*/  elem_size; int /*<<< orphan*/  consumer_counter; } ;
struct mlxsw_pci {int /*<<< orphan*/  core; struct pci_dev* pdev; } ;
typedef  enum mlxsw_pci_cqe_v { ____Placeholder_mlxsw_pci_cqe_v } mlxsw_pci_cqe_v ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ ETH_FCS_LEN ; 
 int /*<<< orphan*/  dev_dbg_ratelimited (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_core_skb_receive (int /*<<< orphan*/ ,struct sk_buff*,struct mlxsw_rx_info*) ; 
 scalar_t__ mlxsw_pci_cqe_byte_count_get (char*) ; 
 scalar_t__ mlxsw_pci_cqe_crc_get (int,char*) ; 
 scalar_t__ mlxsw_pci_cqe_lag_get (int,char*) ; 
 int /*<<< orphan*/  mlxsw_pci_cqe_lag_id_get (int,char*) ; 
 int /*<<< orphan*/  mlxsw_pci_cqe_lag_subport_get (int,char*) ; 
 int /*<<< orphan*/  mlxsw_pci_cqe_system_port_get (char*) ; 
 int /*<<< orphan*/  mlxsw_pci_cqe_trap_id_get (char*) ; 
 int /*<<< orphan*/  mlxsw_pci_queue_doorbell_producer_ring (struct mlxsw_pci*,struct mlxsw_pci_queue*) ; 
 struct mlxsw_pci_queue_elem_info* mlxsw_pci_queue_elem_info_consumer_get (struct mlxsw_pci_queue*) ; 
 int mlxsw_pci_rdq_skb_alloc (struct mlxsw_pci*,struct mlxsw_pci_queue_elem_info*) ; 
 int /*<<< orphan*/  mlxsw_pci_wqe_frag_unmap (struct mlxsw_pci*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static void mlxsw_pci_cqe_rdq_handle(struct mlxsw_pci *mlxsw_pci,
				     struct mlxsw_pci_queue *q,
				     u16 consumer_counter_limit,
				     enum mlxsw_pci_cqe_v cqe_v, char *cqe)
{
	struct pci_dev *pdev = mlxsw_pci->pdev;
	struct mlxsw_pci_queue_elem_info *elem_info;
	char *wqe;
	struct sk_buff *skb;
	struct mlxsw_rx_info rx_info;
	u16 byte_count;
	int err;

	elem_info = mlxsw_pci_queue_elem_info_consumer_get(q);
	skb = elem_info->u.sdq.skb;
	if (!skb)
		return;
	wqe = elem_info->elem;
	mlxsw_pci_wqe_frag_unmap(mlxsw_pci, wqe, 0, DMA_FROM_DEVICE);

	if (q->consumer_counter++ != consumer_counter_limit)
		dev_dbg_ratelimited(&pdev->dev, "Consumer counter does not match limit in RDQ\n");

	if (mlxsw_pci_cqe_lag_get(cqe_v, cqe)) {
		rx_info.is_lag = true;
		rx_info.u.lag_id = mlxsw_pci_cqe_lag_id_get(cqe_v, cqe);
		rx_info.lag_port_index =
			mlxsw_pci_cqe_lag_subport_get(cqe_v, cqe);
	} else {
		rx_info.is_lag = false;
		rx_info.u.sys_port = mlxsw_pci_cqe_system_port_get(cqe);
	}

	rx_info.trap_id = mlxsw_pci_cqe_trap_id_get(cqe);

	byte_count = mlxsw_pci_cqe_byte_count_get(cqe);
	if (mlxsw_pci_cqe_crc_get(cqe_v, cqe))
		byte_count -= ETH_FCS_LEN;
	skb_put(skb, byte_count);
	mlxsw_core_skb_receive(mlxsw_pci->core, skb, &rx_info);

	memset(wqe, 0, q->elem_size);
	err = mlxsw_pci_rdq_skb_alloc(mlxsw_pci, elem_info);
	if (err)
		dev_dbg_ratelimited(&pdev->dev, "Failed to alloc skb for RDQ\n");
	/* Everything is set up, ring doorbell to pass elem to HW */
	q->producer_counter++;
	mlxsw_pci_queue_doorbell_producer_ring(mlxsw_pci, q);
	return;
}