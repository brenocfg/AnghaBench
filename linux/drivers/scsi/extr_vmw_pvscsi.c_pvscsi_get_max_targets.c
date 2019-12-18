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
typedef  int u64 ;
typedef  int u32 ;
struct pvscsi_adapter {TYPE_1__* dev; } ;
struct device {int dummy; } ;
struct PVSCSIConfigPageHeader {scalar_t__ hostStatus; scalar_t__ scsiStatus; } ;
struct PVSCSIConfigPageController {int numPhys; } ;
struct PVSCSICmdDescConfigCmd {int configPageAddress; int cmpAddr; scalar_t__ _pad; int /*<<< orphan*/  configPageNum; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BTSTAT_INVPARAM ; 
 scalar_t__ BTSTAT_SUCCESS ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PVSCSI_CMD_CONFIG ; 
 scalar_t__ PVSCSI_CONFIG_CONTROLLER_ADDRESS ; 
 int /*<<< orphan*/  PVSCSI_CONFIG_PAGE_CONTROLLER ; 
 scalar_t__ SDSTAT_CHECK ; 
 scalar_t__ SDSTAT_GOOD ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  memset (struct PVSCSIConfigPageHeader*,int /*<<< orphan*/ ,int) ; 
 struct device* pvscsi_dev (struct pvscsi_adapter*) ; 
 int /*<<< orphan*/  pvscsi_write_cmd_desc (struct pvscsi_adapter*,int /*<<< orphan*/ ,struct PVSCSICmdDescConfigCmd*,int) ; 

__attribute__((used)) static u32 pvscsi_get_max_targets(struct pvscsi_adapter *adapter)
{
	struct PVSCSICmdDescConfigCmd cmd;
	struct PVSCSIConfigPageHeader *header;
	struct device *dev;
	dma_addr_t configPagePA;
	void *config_page;
	u32 numPhys = 16;

	dev = pvscsi_dev(adapter);
	config_page = dma_alloc_coherent(&adapter->dev->dev, PAGE_SIZE,
			&configPagePA, GFP_KERNEL);
	if (!config_page) {
		dev_warn(dev, "vmw_pvscsi: failed to allocate memory for config page\n");
		goto exit;
	}
	BUG_ON(configPagePA & ~PAGE_MASK);

	/* Fetch config info from the device. */
	cmd.configPageAddress = ((u64)PVSCSI_CONFIG_CONTROLLER_ADDRESS) << 32;
	cmd.configPageNum = PVSCSI_CONFIG_PAGE_CONTROLLER;
	cmd.cmpAddr = configPagePA;
	cmd._pad = 0;

	/*
	 * Mark the completion page header with error values. If the device
	 * completes the command successfully, it sets the status values to
	 * indicate success.
	 */
	header = config_page;
	memset(header, 0, sizeof *header);
	header->hostStatus = BTSTAT_INVPARAM;
	header->scsiStatus = SDSTAT_CHECK;

	pvscsi_write_cmd_desc(adapter, PVSCSI_CMD_CONFIG, &cmd, sizeof cmd);

	if (header->hostStatus == BTSTAT_SUCCESS &&
	    header->scsiStatus == SDSTAT_GOOD) {
		struct PVSCSIConfigPageController *config;

		config = config_page;
		numPhys = config->numPhys;
	} else
		dev_warn(dev, "vmw_pvscsi: PVSCSI_CMD_CONFIG failed. hostStatus = 0x%x, scsiStatus = 0x%x\n",
			 header->hostStatus, header->scsiStatus);
	dma_free_coherent(&adapter->dev->dev, PAGE_SIZE, config_page,
			  configPagePA);
exit:
	return numPhys;
}