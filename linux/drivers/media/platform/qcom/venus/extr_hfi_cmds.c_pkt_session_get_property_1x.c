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
struct TYPE_4__ {int /*<<< orphan*/  session_id; TYPE_1__ hdr; } ;
struct hfi_session_get_property_pkt {int num_properties; int* data; TYPE_2__ shdr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HFI_CMD_SESSION_GET_PROPERTY ; 
#define  HFI_PROPERTY_CONFIG_BUFFER_REQUIREMENTS 129 
#define  HFI_PROPERTY_PARAM_PROFILE_LEVEL_CURRENT 128 
 int /*<<< orphan*/  hash32_ptr (void*) ; 

__attribute__((used)) static int pkt_session_get_property_1x(struct hfi_session_get_property_pkt *pkt,
				       void *cookie, u32 ptype)
{
	switch (ptype) {
	case HFI_PROPERTY_PARAM_PROFILE_LEVEL_CURRENT:
	case HFI_PROPERTY_CONFIG_BUFFER_REQUIREMENTS:
		break;
	default:
		return -EINVAL;
	}

	pkt->shdr.hdr.size = sizeof(*pkt);
	pkt->shdr.hdr.pkt_type = HFI_CMD_SESSION_GET_PROPERTY;
	pkt->shdr.session_id = hash32_ptr(cookie);
	pkt->num_properties = 1;
	pkt->data[0] = ptype;

	return 0;
}