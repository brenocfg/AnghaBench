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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct pcie_service_card {scalar_t__ sleep_cookie_pbase; scalar_t__ sleep_cookie_vbase; scalar_t__ evtbd_ring_pbase; scalar_t__ rxbd_ring_pbase; scalar_t__ txbd_ring_pbase; } ;
struct mwifiex_private {TYPE_2__* adapter; } ;
struct host_cmd_ds_pcie_details {void* sleep_cookie_addr_lo; void* sleep_cookie_addr_hi; void* evtbd_count; void* evtbd_addr_hi; void* evtbd_addr_lo; void* rxbd_count; void* rxbd_addr_hi; void* rxbd_addr_lo; void* txbd_count; void* txbd_addr_hi; void* txbd_addr_lo; } ;
struct TYPE_3__ {struct host_cmd_ds_pcie_details pcie_host_spec; } ;
struct host_cmd_ds_command {scalar_t__ result; void* size; void* command; TYPE_1__ params; } ;
struct TYPE_4__ {struct pcie_service_card* card; } ;

/* Variables and functions */
 scalar_t__ HostCmd_ACT_GEN_SET ; 
 scalar_t__ HostCmd_CMD_PCIE_DESC_DETAILS ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  MWIFIEX_MAX_EVT_BD ; 
 int /*<<< orphan*/  MWIFIEX_MAX_TXRX_BD ; 
 scalar_t__ S_DS_GEN ; 
 void* cpu_to_le16 (scalar_t__) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct host_cmd_ds_pcie_details*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mwifiex_dbg (TYPE_2__*,int /*<<< orphan*/ ,char*,void*) ; 

__attribute__((used)) static int
mwifiex_cmd_pcie_host_spec(struct mwifiex_private *priv,
			   struct host_cmd_ds_command *cmd, u16 action)
{
	struct host_cmd_ds_pcie_details *host_spec =
					&cmd->params.pcie_host_spec;
	struct pcie_service_card *card = priv->adapter->card;

	cmd->command = cpu_to_le16(HostCmd_CMD_PCIE_DESC_DETAILS);
	cmd->size = cpu_to_le16(sizeof(struct
					host_cmd_ds_pcie_details) + S_DS_GEN);
	cmd->result = 0;

	memset(host_spec, 0, sizeof(struct host_cmd_ds_pcie_details));

	if (action != HostCmd_ACT_GEN_SET)
		return 0;

	/* Send the ring base addresses and count to firmware */
	host_spec->txbd_addr_lo = cpu_to_le32((u32)(card->txbd_ring_pbase));
	host_spec->txbd_addr_hi =
			cpu_to_le32((u32)(((u64)card->txbd_ring_pbase) >> 32));
	host_spec->txbd_count = cpu_to_le32(MWIFIEX_MAX_TXRX_BD);
	host_spec->rxbd_addr_lo = cpu_to_le32((u32)(card->rxbd_ring_pbase));
	host_spec->rxbd_addr_hi =
			cpu_to_le32((u32)(((u64)card->rxbd_ring_pbase) >> 32));
	host_spec->rxbd_count = cpu_to_le32(MWIFIEX_MAX_TXRX_BD);
	host_spec->evtbd_addr_lo = cpu_to_le32((u32)(card->evtbd_ring_pbase));
	host_spec->evtbd_addr_hi =
			cpu_to_le32((u32)(((u64)card->evtbd_ring_pbase) >> 32));
	host_spec->evtbd_count = cpu_to_le32(MWIFIEX_MAX_EVT_BD);
	if (card->sleep_cookie_vbase) {
		host_spec->sleep_cookie_addr_lo =
				cpu_to_le32((u32)(card->sleep_cookie_pbase));
		host_spec->sleep_cookie_addr_hi = cpu_to_le32((u32)(((u64)
					(card->sleep_cookie_pbase)) >> 32));
		mwifiex_dbg(priv->adapter, INFO,
			    "sleep_cook_lo phy addr: 0x%x\n",
			    host_spec->sleep_cookie_addr_lo);
	}

	return 0;
}