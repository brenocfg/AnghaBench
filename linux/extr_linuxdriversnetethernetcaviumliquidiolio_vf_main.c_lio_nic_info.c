#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union oct_link_status {int dummy; } oct_link_status ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {int gmxport; } ;
struct TYPE_7__ {TYPE_2__ r_nic_info; } ;
struct octeon_recv_pkt {scalar_t__* buffer_size; int buffer_count; int /*<<< orphan*/ * buffer_ptr; TYPE_3__ rh; } ;
struct octeon_recv_info {struct octeon_recv_pkt* recv_pkt; } ;
struct octeon_device {int ifcount; TYPE_4__* props; TYPE_1__* pci_dev; } ;
struct TYPE_8__ {int gmxport; int /*<<< orphan*/  netdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ OCT_DROQ_INFO_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,int) ; 
 scalar_t__ get_rbd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_free_recv_info (struct octeon_recv_info*) ; 
 int /*<<< orphan*/  octeon_swap_8B_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  recv_buffer_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_link_status (int /*<<< orphan*/ ,union oct_link_status*) ; 

__attribute__((used)) static int lio_nic_info(struct octeon_recv_info *recv_info, void *buf)
{
	struct octeon_device *oct = (struct octeon_device *)buf;
	struct octeon_recv_pkt *recv_pkt = recv_info->recv_pkt;
	union oct_link_status *ls;
	int gmxport = 0;
	int i;

	if (recv_pkt->buffer_size[0] != (sizeof(*ls) + OCT_DROQ_INFO_SIZE)) {
		dev_err(&oct->pci_dev->dev, "Malformed NIC_INFO, len=%d, ifidx=%d\n",
			recv_pkt->buffer_size[0],
			recv_pkt->rh.r_nic_info.gmxport);
		goto nic_info_err;
	}

	gmxport = recv_pkt->rh.r_nic_info.gmxport;
	ls = (union oct_link_status *)(get_rbd(recv_pkt->buffer_ptr[0]) +
		OCT_DROQ_INFO_SIZE);

	octeon_swap_8B_data((u64 *)ls, (sizeof(union oct_link_status)) >> 3);

	for (i = 0; i < oct->ifcount; i++) {
		if (oct->props[i].gmxport == gmxport) {
			update_link_status(oct->props[i].netdev, ls);
			break;
		}
	}

nic_info_err:
	for (i = 0; i < recv_pkt->buffer_count; i++)
		recv_buffer_free(recv_pkt->buffer_ptr[i]);
	octeon_free_recv_info(recv_info);
	return 0;
}