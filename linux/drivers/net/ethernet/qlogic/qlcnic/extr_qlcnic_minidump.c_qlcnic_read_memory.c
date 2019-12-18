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
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_fw_dump {scalar_t__ use_pex_dma; } ;
struct TYPE_7__ {int /*<<< orphan*/  mask; } ;
struct __mem {int dummy; } ;
struct TYPE_6__ {struct __mem mem; } ;
struct qlcnic_dump_entry {TYPE_3__ hdr; TYPE_2__ region; } ;
struct qlcnic_adapter {TYPE_1__* pdev; TYPE_4__* ahw; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_8__ {struct qlcnic_fw_dump fw_dump; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_read_memory_pexdma (struct qlcnic_adapter*,struct __mem*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  qlcnic_read_memory_test_agent (struct qlcnic_adapter*,struct __mem*,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static u32 qlcnic_read_memory(struct qlcnic_adapter *adapter,
			      struct qlcnic_dump_entry *entry, __le32 *buffer)
{
	struct qlcnic_fw_dump *fw_dump = &adapter->ahw->fw_dump;
	struct device *dev = &adapter->pdev->dev;
	struct __mem *mem = &entry->region.mem;
	u32 data_size;
	int ret = 0;

	if (fw_dump->use_pex_dma) {
		data_size = qlcnic_read_memory_pexdma(adapter, mem, buffer,
						      &ret);
		if (ret)
			dev_info(dev,
				 "Failed to read memory dump using PEX DMA: mask[0x%x]\n",
				 entry->hdr.mask);
		else
			return data_size;
	}

	data_size = qlcnic_read_memory_test_agent(adapter, mem, buffer, &ret);
	if (ret) {
		dev_info(dev,
			 "Failed to read memory dump using test agent method: mask[0x%x]\n",
			 entry->hdr.mask);
		return 0;
	} else {
		return data_size;
	}
}