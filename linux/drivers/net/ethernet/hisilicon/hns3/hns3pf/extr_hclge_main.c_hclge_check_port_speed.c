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
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct TYPE_3__ {int speed_ability; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct hclge_dev {TYPE_2__ hw; } ;

/* Variables and functions */
 int EINVAL ; 
#define  HCLGE_MAC_SPEED_100G 135 
#define  HCLGE_MAC_SPEED_100M 134 
#define  HCLGE_MAC_SPEED_10G 133 
#define  HCLGE_MAC_SPEED_10M 132 
#define  HCLGE_MAC_SPEED_1G 131 
#define  HCLGE_MAC_SPEED_25G 130 
#define  HCLGE_MAC_SPEED_40G 129 
#define  HCLGE_MAC_SPEED_50G 128 
 int HCLGE_SUPPORT_100G_BIT ; 
 int HCLGE_SUPPORT_100M_BIT ; 
 int HCLGE_SUPPORT_10G_BIT ; 
 int HCLGE_SUPPORT_10M_BIT ; 
 int HCLGE_SUPPORT_1G_BIT ; 
 int HCLGE_SUPPORT_25G_BIT ; 
 int HCLGE_SUPPORT_40G_BIT ; 
 int HCLGE_SUPPORT_50G_BIT ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 

__attribute__((used)) static int hclge_check_port_speed(struct hnae3_handle *handle, u32 speed)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	u32 speed_ability = hdev->hw.mac.speed_ability;
	u32 speed_bit = 0;

	switch (speed) {
	case HCLGE_MAC_SPEED_10M:
		speed_bit = HCLGE_SUPPORT_10M_BIT;
		break;
	case HCLGE_MAC_SPEED_100M:
		speed_bit = HCLGE_SUPPORT_100M_BIT;
		break;
	case HCLGE_MAC_SPEED_1G:
		speed_bit = HCLGE_SUPPORT_1G_BIT;
		break;
	case HCLGE_MAC_SPEED_10G:
		speed_bit = HCLGE_SUPPORT_10G_BIT;
		break;
	case HCLGE_MAC_SPEED_25G:
		speed_bit = HCLGE_SUPPORT_25G_BIT;
		break;
	case HCLGE_MAC_SPEED_40G:
		speed_bit = HCLGE_SUPPORT_40G_BIT;
		break;
	case HCLGE_MAC_SPEED_50G:
		speed_bit = HCLGE_SUPPORT_50G_BIT;
		break;
	case HCLGE_MAC_SPEED_100G:
		speed_bit = HCLGE_SUPPORT_100G_BIT;
		break;
	default:
		return -EINVAL;
	}

	if (speed_bit & speed_ability)
		return 0;

	return -EINVAL;
}