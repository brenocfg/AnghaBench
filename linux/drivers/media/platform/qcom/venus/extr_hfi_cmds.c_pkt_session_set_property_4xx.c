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
typedef  int u32 ;
struct hfi_videocores_usage_type {int /*<<< orphan*/  video_core_enable_mask; } ;
struct hfi_video_work_mode {int /*<<< orphan*/  video_work_mode; } ;
struct TYPE_3__ {int size; int /*<<< orphan*/  pkt_type; } ;
struct TYPE_4__ {TYPE_1__ hdr; int /*<<< orphan*/  session_id; } ;
struct hfi_session_set_property_pkt {int* data; int num_properties; TYPE_2__ shdr; } ;
struct hfi_buffer_count_actual_4xx {int /*<<< orphan*/  count_min_host; int /*<<< orphan*/  type; int /*<<< orphan*/  count_actual; } ;
struct hfi_buffer_count_actual {int /*<<< orphan*/  count_actual; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  HFI_CMD_SESSION_SET_PROPERTY ; 
#define  HFI_PROPERTY_CONFIG_VDEC_POST_LOOP_DEBLOCKER 133 
#define  HFI_PROPERTY_CONFIG_VENC_MAX_BITRATE 132 
#define  HFI_PROPERTY_CONFIG_VIDEOCORES_USAGE 131 
#define  HFI_PROPERTY_PARAM_BUFFER_ALLOC_MODE 130 
#define  HFI_PROPERTY_PARAM_BUFFER_COUNT_ACTUAL 129 
#define  HFI_PROPERTY_PARAM_WORK_MODE 128 
 int /*<<< orphan*/  hash32_ptr (void*) ; 
 int pkt_session_set_property_3xx (struct hfi_session_set_property_pkt*,void*,int,void*) ; 

__attribute__((used)) static int
pkt_session_set_property_4xx(struct hfi_session_set_property_pkt *pkt,
			     void *cookie, u32 ptype, void *pdata)
{
	void *prop_data;

	if (!pkt || !cookie || !pdata)
		return -EINVAL;

	prop_data = &pkt->data[1];

	pkt->shdr.hdr.size = sizeof(*pkt);
	pkt->shdr.hdr.pkt_type = HFI_CMD_SESSION_SET_PROPERTY;
	pkt->shdr.session_id = hash32_ptr(cookie);
	pkt->num_properties = 1;
	pkt->data[0] = ptype;

	/*
	 * Any session set property which is different in 3XX packetization
	 * should be added as a new case below. All unchanged session set
	 * properties will be handled in the default case.
	 */
	switch (ptype) {
	case HFI_PROPERTY_PARAM_BUFFER_COUNT_ACTUAL: {
		struct hfi_buffer_count_actual *in = pdata;
		struct hfi_buffer_count_actual_4xx *count = prop_data;

		count->count_actual = in->count_actual;
		count->type = in->type;
		count->count_min_host = in->count_actual;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*count);
		break;
	}
	case HFI_PROPERTY_PARAM_WORK_MODE: {
		struct hfi_video_work_mode *in = pdata, *wm = prop_data;

		wm->video_work_mode = in->video_work_mode;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*wm);
		break;
	}
	case HFI_PROPERTY_CONFIG_VIDEOCORES_USAGE: {
		struct hfi_videocores_usage_type *in = pdata, *cu = prop_data;

		cu->video_core_enable_mask = in->video_core_enable_mask;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*cu);
		break;
	}
	case HFI_PROPERTY_CONFIG_VENC_MAX_BITRATE:
	case HFI_PROPERTY_CONFIG_VDEC_POST_LOOP_DEBLOCKER:
	case HFI_PROPERTY_PARAM_BUFFER_ALLOC_MODE:
		/* not implemented on Venus 4xx */
		return -ENOTSUPP;
	default:
		return pkt_session_set_property_3xx(pkt, cookie, ptype, pdata);
	}

	return 0;
}