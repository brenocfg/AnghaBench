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
struct TYPE_3__ {int size; int /*<<< orphan*/  pkt_type; } ;
struct TYPE_4__ {TYPE_1__ hdr; int /*<<< orphan*/  session_id; } ;
struct hfi_session_set_property_pkt {int* data; int num_properties; TYPE_2__ shdr; } ;
struct hfi_multi_stream_3x {int /*<<< orphan*/  enable; int /*<<< orphan*/  buffer_type; } ;
struct hfi_multi_stream {int /*<<< orphan*/  enable; int /*<<< orphan*/  buffer_type; } ;
struct hfi_intra_refresh_3x {int /*<<< orphan*/  mbs; int /*<<< orphan*/  mode; } ;
struct hfi_intra_refresh {int /*<<< orphan*/  cir_mbs; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HFI_CMD_SESSION_SET_PROPERTY ; 
#define  HFI_INTRA_REFRESH_ADAPTIVE 135 
#define  HFI_INTRA_REFRESH_CYCLIC 134 
#define  HFI_INTRA_REFRESH_CYCLIC_ADAPTIVE 133 
#define  HFI_INTRA_REFRESH_NONE 132 
#define  HFI_INTRA_REFRESH_RANDOM 131 
#define  HFI_PROPERTY_PARAM_VDEC_CONTINUE_DATA_TRANSFER 130 
#define  HFI_PROPERTY_PARAM_VDEC_MULTI_STREAM 129 
#define  HFI_PROPERTY_PARAM_VENC_INTRA_REFRESH 128 
 int /*<<< orphan*/  hash32_ptr (void*) ; 
 int pkt_session_set_property_1x (struct hfi_session_set_property_pkt*,void*,int,void*) ; 

__attribute__((used)) static int
pkt_session_set_property_3xx(struct hfi_session_set_property_pkt *pkt,
			     void *cookie, u32 ptype, void *pdata)
{
	void *prop_data;
	int ret = 0;

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
	case HFI_PROPERTY_PARAM_VDEC_MULTI_STREAM: {
		struct hfi_multi_stream *in = pdata;
		struct hfi_multi_stream_3x *multi = prop_data;

		multi->buffer_type = in->buffer_type;
		multi->enable = in->enable;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*multi);
		break;
	}
	case HFI_PROPERTY_PARAM_VENC_INTRA_REFRESH: {
		struct hfi_intra_refresh *in = pdata;
		struct hfi_intra_refresh_3x *intra = prop_data;

		switch (in->mode) {
		case HFI_INTRA_REFRESH_NONE:
		case HFI_INTRA_REFRESH_ADAPTIVE:
		case HFI_INTRA_REFRESH_CYCLIC:
		case HFI_INTRA_REFRESH_CYCLIC_ADAPTIVE:
		case HFI_INTRA_REFRESH_RANDOM:
			break;
		default:
			ret = -EINVAL;
			break;
		}

		intra->mode = in->mode;
		intra->mbs = in->cir_mbs;
		pkt->shdr.hdr.size += sizeof(u32) + sizeof(*intra);
		break;
	}
	case HFI_PROPERTY_PARAM_VDEC_CONTINUE_DATA_TRANSFER:
		/* for 3xx fw version session_continue is used */
		break;
	default:
		ret = pkt_session_set_property_1x(pkt, cookie, ptype, pdata);
		break;
	}

	return ret;
}