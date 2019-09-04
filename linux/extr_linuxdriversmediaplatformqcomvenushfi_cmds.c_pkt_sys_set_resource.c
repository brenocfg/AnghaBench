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
typedef  int u32 ;
struct TYPE_2__ {int size; int /*<<< orphan*/  pkt_type; } ;
struct hfi_sys_set_resource_pkt {TYPE_1__ hdr; int /*<<< orphan*/  resource_type; int /*<<< orphan*/ * resource_data; int /*<<< orphan*/  resource_handle; } ;
struct hfi_resource_ocmem {int size; int mem; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  HFI_CMD_SYS_SET_RESOURCE ; 
 int /*<<< orphan*/  HFI_RESOURCE_OCMEM ; 
#define  VIDC_RESOURCE_NONE 130 
#define  VIDC_RESOURCE_OCMEM 129 
#define  VIDC_RESOURCE_VMEM 128 
 int /*<<< orphan*/  hash32_ptr (void*) ; 

int pkt_sys_set_resource(struct hfi_sys_set_resource_pkt *pkt, u32 id, u32 size,
			 u32 addr, void *cookie)
{
	pkt->hdr.size = sizeof(*pkt);
	pkt->hdr.pkt_type = HFI_CMD_SYS_SET_RESOURCE;
	pkt->resource_handle = hash32_ptr(cookie);

	switch (id) {
	case VIDC_RESOURCE_OCMEM:
	case VIDC_RESOURCE_VMEM: {
		struct hfi_resource_ocmem *res =
			(struct hfi_resource_ocmem *)&pkt->resource_data[0];

		res->size = size;
		res->mem = addr;
		pkt->resource_type = HFI_RESOURCE_OCMEM;
		pkt->hdr.size += sizeof(*res) - sizeof(u32);
		break;
	}
	case VIDC_RESOURCE_NONE:
	default:
		return -ENOTSUPP;
	}

	return 0;
}