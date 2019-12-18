#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct qlcnic_fw_dump {int clr; int cap_mask; int size; int num_entries; int offset; void* tmpl_hdr; int /*<<< orphan*/  tmpl_hdr_size; int /*<<< orphan*/ * data; } ;
struct qlcnic_hardware_context {size_t pci_func; struct qlcnic_fw_dump fw_dump; } ;
struct qlcnic_dump_operations {scalar_t__ opcode; int (* handler ) (struct qlcnic_adapter*,struct qlcnic_dump_entry*,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {int mask; int offset; scalar_t__ type; int cap_size; int /*<<< orphan*/  flags; } ;
struct qlcnic_dump_entry {TYPE_2__ hdr; } ;
struct qlcnic_adapter {TYPE_3__* netdev; int /*<<< orphan*/  fw_version; struct qlcnic_hardware_context* ahw; TYPE_1__* pdev; } ;
struct qlcnic_83xx_dump_template_hdr {int* ocm_wnd_reg; int* saved_state; } ;
struct device {int /*<<< orphan*/  kobj; } ;
typedef  int /*<<< orphan*/  mesg ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_7__ {char* name; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct qlcnic_dump_operations*) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  QLCNIC_DRIVER_VERSION ; 
 int QLCNIC_DUMP_MASK_MAX ; 
 int /*<<< orphan*/  QLCNIC_DUMP_SKIP ; 
 size_t QLC_83XX_OCM_INDEX ; 
 size_t QLC_83XX_PCI_INDEX ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  kobject_uevent_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  netdev_info (TYPE_3__*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  netif_info (struct qlcnic_hardware_context*,int /*<<< orphan*/ ,TYPE_3__*,char*) ; 
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 struct qlcnic_dump_operations* qlcnic_83xx_fw_dump_ops ; 
 int /*<<< orphan*/  qlcnic_check_fw_dump_state (struct qlcnic_adapter*) ; 
 struct qlcnic_dump_operations* qlcnic_fw_dump_ops ; 
 scalar_t__ qlcnic_get_cap_size (struct qlcnic_adapter*,void*,int) ; 
 int /*<<< orphan*/  qlcnic_set_sys_info (struct qlcnic_adapter*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_valid_dump_entry (struct device*,struct qlcnic_dump_entry*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int stub1 (struct qlcnic_adapter*,struct qlcnic_dump_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vzalloc (int) ; 

int qlcnic_dump_fw(struct qlcnic_adapter *adapter)
{
	struct qlcnic_fw_dump *fw_dump = &adapter->ahw->fw_dump;
	const struct qlcnic_dump_operations *fw_dump_ops;
	struct qlcnic_83xx_dump_template_hdr *hdr_83xx;
	u32 entry_offset, dump, no_entries, buf_offset = 0;
	int i, k, ops_cnt, ops_index, dump_size = 0;
	struct device *dev = &adapter->pdev->dev;
	struct qlcnic_hardware_context *ahw;
	struct qlcnic_dump_entry *entry;
	void *tmpl_hdr;
	u32 ocm_window;
	__le32 *buffer;
	char mesg[64];
	char *msg[] = {mesg, NULL};

	ahw = adapter->ahw;
	tmpl_hdr = fw_dump->tmpl_hdr;

	/* Return if we don't have firmware dump template header */
	if (!tmpl_hdr)
		return -EIO;

	if (!qlcnic_check_fw_dump_state(adapter)) {
		dev_info(&adapter->pdev->dev, "Dump not enabled\n");
		return -EIO;
	}

	if (fw_dump->clr) {
		dev_info(&adapter->pdev->dev,
			 "Previous dump not cleared, not capturing dump\n");
		return -EIO;
	}

	netif_info(adapter->ahw, drv, adapter->netdev, "Take FW dump\n");
	/* Calculate the size for dump data area only */
	for (i = 2, k = 1; (i & QLCNIC_DUMP_MASK_MAX); i <<= 1, k++)
		if (i & fw_dump->cap_mask)
			dump_size += qlcnic_get_cap_size(adapter, tmpl_hdr, k);

	if (!dump_size)
		return -EIO;

	fw_dump->data = vzalloc(dump_size);
	if (!fw_dump->data)
		return -ENOMEM;

	buffer = fw_dump->data;
	fw_dump->size = dump_size;
	no_entries = fw_dump->num_entries;
	entry_offset = fw_dump->offset;
	qlcnic_set_sys_info(adapter, tmpl_hdr, 0, QLCNIC_DRIVER_VERSION);
	qlcnic_set_sys_info(adapter, tmpl_hdr, 1, adapter->fw_version);

	if (qlcnic_82xx_check(adapter)) {
		ops_cnt = ARRAY_SIZE(qlcnic_fw_dump_ops);
		fw_dump_ops = qlcnic_fw_dump_ops;
	} else {
		hdr_83xx = tmpl_hdr;
		ops_cnt = ARRAY_SIZE(qlcnic_83xx_fw_dump_ops);
		fw_dump_ops = qlcnic_83xx_fw_dump_ops;
		ocm_window = hdr_83xx->ocm_wnd_reg[ahw->pci_func];
		hdr_83xx->saved_state[QLC_83XX_OCM_INDEX] = ocm_window;
		hdr_83xx->saved_state[QLC_83XX_PCI_INDEX] = ahw->pci_func;
	}

	for (i = 0; i < no_entries; i++) {
		entry = tmpl_hdr + entry_offset;
		if (!(entry->hdr.mask & fw_dump->cap_mask)) {
			entry->hdr.flags |= QLCNIC_DUMP_SKIP;
			entry_offset += entry->hdr.offset;
			continue;
		}

		/* Find the handler for this entry */
		ops_index = 0;
		while (ops_index < ops_cnt) {
			if (entry->hdr.type == fw_dump_ops[ops_index].opcode)
				break;
			ops_index++;
		}

		if (ops_index == ops_cnt) {
			dev_info(dev, "Skipping unknown entry opcode %d\n",
				 entry->hdr.type);
			entry->hdr.flags |= QLCNIC_DUMP_SKIP;
			entry_offset += entry->hdr.offset;
			continue;
		}

		/* Collect dump for this entry */
		dump = fw_dump_ops[ops_index].handler(adapter, entry, buffer);
		if (!qlcnic_valid_dump_entry(dev, entry, dump)) {
			entry->hdr.flags |= QLCNIC_DUMP_SKIP;
			entry_offset += entry->hdr.offset;
			continue;
		}

		buf_offset += entry->hdr.cap_size;
		entry_offset += entry->hdr.offset;
		buffer = fw_dump->data + buf_offset;
	}

	fw_dump->clr = 1;
	snprintf(mesg, sizeof(mesg), "FW_DUMP=%s", adapter->netdev->name);
	netdev_info(adapter->netdev,
		    "Dump data %d bytes captured, dump data address = %p, template header size %d bytes, template address = %p\n",
		    fw_dump->size, fw_dump->data, fw_dump->tmpl_hdr_size,
		    fw_dump->tmpl_hdr);
	/* Send a udev event to notify availability of FW dump */
	kobject_uevent_env(&dev->kobj, KOBJ_CHANGE, msg);

	return 0;
}