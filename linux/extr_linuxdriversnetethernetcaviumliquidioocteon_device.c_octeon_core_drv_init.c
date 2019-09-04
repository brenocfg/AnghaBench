#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_11__ {scalar_t__ app_mode; int /*<<< orphan*/  pkind; int /*<<< orphan*/  app_cap_flags; scalar_t__ num_gmx_ports; scalar_t__ max_nic_ports; } ;
struct TYPE_12__ {TYPE_2__ r_core_drv_init; } ;
struct octeon_recv_pkt {scalar_t__* buffer_size; scalar_t__ buffer_count; int /*<<< orphan*/ * buffer_ptr; TYPE_3__ rh; } ;
struct octeon_recv_info {struct octeon_recv_pkt* recv_pkt; } ;
struct TYPE_17__ {char* name; char* serial_number; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct TYPE_16__ {int /*<<< orphan*/  pkind; scalar_t__ app_mode; } ;
struct TYPE_10__ {scalar_t__ max_nic_ports; scalar_t__ app_mode; int /*<<< orphan*/  app_cap_flags; scalar_t__ num_gmx_ports; } ;
struct octeon_device {scalar_t__ num_iqs; size_t octeon_id; TYPE_9__* pci_dev; TYPE_8__ boardinfo; int /*<<< orphan*/  status; TYPE_7__ pfvf_hsword; TYPE_6__** instr_queue; TYPE_1__ fw_info; scalar_t__ app_mode; } ;
struct octeon_core_setup {int /*<<< orphan*/  corefreq; int /*<<< orphan*/  board_rev_minor; int /*<<< orphan*/  board_rev_major; int /*<<< orphan*/  board_serial_number; int /*<<< orphan*/  boardname; } ;
typedef  int /*<<< orphan*/  app_name ;
struct TYPE_18__ {int /*<<< orphan*/  dev; } ;
struct TYPE_13__ {int /*<<< orphan*/  pkind; } ;
struct TYPE_14__ {TYPE_4__ s; } ;
struct TYPE_15__ {TYPE_5__ txpciq; } ;

/* Variables and functions */
 scalar_t__ CFG_GET_NUM_NIC_PORTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHIP_CONF (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVM_CAST64 (int /*<<< orphan*/ ) ; 
 scalar_t__ CVM_DRV_NIC_APP ; 
 scalar_t__ OCTEON_CN23XX_PF (struct octeon_device*) ; 
 scalar_t__ OCTEON_CN6XXX (struct octeon_device*) ; 
 int OCT_BOARD_NAME ; 
 int /*<<< orphan*/  OCT_DEV_CORE_OK ; 
 scalar_t__ OCT_DEV_RUNNING ; 
 scalar_t__ OCT_DROQ_INFO_SIZE ; 
 int OCT_SERIAL_LEN ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cn23xx_pf ; 
 int /*<<< orphan*/  cn6xxx ; 
 struct octeon_core_setup* core_setup ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_oct_app_string (scalar_t__) ; 
 scalar_t__ get_rbd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct octeon_core_setup*,scalar_t__,int) ; 
 int /*<<< orphan*/  octeon_free_recv_info (struct octeon_recv_info*) ; 
 int /*<<< orphan*/  octeon_swap_8B_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  recv_buffer_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

int octeon_core_drv_init(struct octeon_recv_info *recv_info, void *buf)
{
	u32 i;
	char app_name[16];
	struct octeon_device *oct = (struct octeon_device *)buf;
	struct octeon_recv_pkt *recv_pkt = recv_info->recv_pkt;
	struct octeon_core_setup *cs = NULL;
	u32 num_nic_ports = 0;

	if (OCTEON_CN6XXX(oct))
		num_nic_ports =
			CFG_GET_NUM_NIC_PORTS(CHIP_CONF(oct, cn6xxx));
	else if (OCTEON_CN23XX_PF(oct))
		num_nic_ports =
			CFG_GET_NUM_NIC_PORTS(CHIP_CONF(oct, cn23xx_pf));

	if (atomic_read(&oct->status) >= OCT_DEV_RUNNING) {
		dev_err(&oct->pci_dev->dev, "Received CORE OK when device state is 0x%x\n",
			atomic_read(&oct->status));
		goto core_drv_init_err;
	}

	strncpy(app_name,
		get_oct_app_string(
		(u32)recv_pkt->rh.r_core_drv_init.app_mode),
		sizeof(app_name) - 1);
	oct->app_mode = (u32)recv_pkt->rh.r_core_drv_init.app_mode;
	if (recv_pkt->rh.r_core_drv_init.app_mode == CVM_DRV_NIC_APP) {
		oct->fw_info.max_nic_ports =
			(u32)recv_pkt->rh.r_core_drv_init.max_nic_ports;
		oct->fw_info.num_gmx_ports =
			(u32)recv_pkt->rh.r_core_drv_init.num_gmx_ports;
	}

	if (oct->fw_info.max_nic_ports < num_nic_ports) {
		dev_err(&oct->pci_dev->dev,
			"Config has more ports than firmware allows (%d > %d).\n",
			num_nic_ports, oct->fw_info.max_nic_ports);
		goto core_drv_init_err;
	}
	oct->fw_info.app_cap_flags = recv_pkt->rh.r_core_drv_init.app_cap_flags;
	oct->fw_info.app_mode = (u32)recv_pkt->rh.r_core_drv_init.app_mode;
	oct->pfvf_hsword.app_mode = (u32)recv_pkt->rh.r_core_drv_init.app_mode;

	oct->pfvf_hsword.pkind = recv_pkt->rh.r_core_drv_init.pkind;

	for (i = 0; i < oct->num_iqs; i++)
		oct->instr_queue[i]->txpciq.s.pkind = oct->pfvf_hsword.pkind;

	atomic_set(&oct->status, OCT_DEV_CORE_OK);

	cs = &core_setup[oct->octeon_id];

	if (recv_pkt->buffer_size[0] != (sizeof(*cs) + OCT_DROQ_INFO_SIZE)) {
		dev_dbg(&oct->pci_dev->dev, "Core setup bytes expected %u found %d\n",
			(u32)sizeof(*cs),
			recv_pkt->buffer_size[0]);
	}

	memcpy(cs, get_rbd(
	       recv_pkt->buffer_ptr[0]) + OCT_DROQ_INFO_SIZE, sizeof(*cs));

	strncpy(oct->boardinfo.name, cs->boardname, OCT_BOARD_NAME);
	strncpy(oct->boardinfo.serial_number, cs->board_serial_number,
		OCT_SERIAL_LEN);

	octeon_swap_8B_data((u64 *)cs, (sizeof(*cs) >> 3));

	oct->boardinfo.major = cs->board_rev_major;
	oct->boardinfo.minor = cs->board_rev_minor;

	dev_info(&oct->pci_dev->dev,
		 "Running %s (%llu Hz)\n",
		 app_name, CVM_CAST64(cs->corefreq));

core_drv_init_err:
	for (i = 0; i < recv_pkt->buffer_count; i++)
		recv_buffer_free(recv_pkt->buffer_ptr[i]);
	octeon_free_recv_info(recv_info);
	return 0;
}