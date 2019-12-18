#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u16 ;
struct wmi_tlv_svc_rdy_parse {int svc_bmap_done; int dbs_hw_mode_done; void const* svc_bmap; void const* mem_reqs; void const* reg; void const* ev; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
#define  WMI_TLV_TAG_ARRAY_STRUCT 131 
#define  WMI_TLV_TAG_ARRAY_UINT32 130 
#define  WMI_TLV_TAG_STRUCT_HAL_REG_CAPABILITIES 129 
#define  WMI_TLV_TAG_STRUCT_SERVICE_READY_EVENT 128 

__attribute__((used)) static int ath10k_wmi_tlv_svc_rdy_parse(struct ath10k *ar, u16 tag, u16 len,
					const void *ptr, void *data)
{
	struct wmi_tlv_svc_rdy_parse *svc_rdy = data;

	switch (tag) {
	case WMI_TLV_TAG_STRUCT_SERVICE_READY_EVENT:
		svc_rdy->ev = ptr;
		break;
	case WMI_TLV_TAG_STRUCT_HAL_REG_CAPABILITIES:
		svc_rdy->reg = ptr;
		break;
	case WMI_TLV_TAG_ARRAY_STRUCT:
		svc_rdy->mem_reqs = ptr;
		break;
	case WMI_TLV_TAG_ARRAY_UINT32:
		if (!svc_rdy->svc_bmap_done) {
			svc_rdy->svc_bmap_done = true;
			svc_rdy->svc_bmap = ptr;
		} else if (!svc_rdy->dbs_hw_mode_done) {
			svc_rdy->dbs_hw_mode_done = true;
		}
		break;
	default:
		break;
	}
	return 0;
}