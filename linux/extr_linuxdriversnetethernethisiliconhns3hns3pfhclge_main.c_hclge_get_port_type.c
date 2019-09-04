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
typedef  int u8 ;
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct TYPE_3__ {int media_type; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct hclge_dev {TYPE_2__ hw; } ;

/* Variables and functions */
#define  HNAE3_MEDIA_TYPE_COPPER 130 
#define  HNAE3_MEDIA_TYPE_FIBER 129 
#define  HNAE3_MEDIA_TYPE_UNKNOWN 128 
 int PORT_FIBRE ; 
 int PORT_OTHER ; 
 int PORT_TP ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 

__attribute__((used)) static void hclge_get_port_type(struct hnae3_handle *handle,
				u8 *port_type)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	u8 media_type = hdev->hw.mac.media_type;

	switch (media_type) {
	case HNAE3_MEDIA_TYPE_FIBER:
		*port_type = PORT_FIBRE;
		break;
	case HNAE3_MEDIA_TYPE_COPPER:
		*port_type = PORT_TP;
		break;
	case HNAE3_MEDIA_TYPE_UNKNOWN:
	default:
		*port_type = PORT_OTHER;
		break;
	}
}