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
struct ican3_fast_desc {int command; int* data; } ;
struct ican3_dev {int dummy; } ;
struct can_frame {int can_id; void* can_dlc; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int CAN_EFF_FLAG ; 
 int CAN_RTR_FLAG ; 
 int ICAN3_CAN_DLC_MASK ; 
 int ICAN3_CAN_TYPE_MASK ; 
 int ICAN3_CAN_TYPE_SFF ; 
 int ICAN3_EFF ; 
 int ICAN3_EFF_RTR ; 
 int ICAN3_SFF_RTR ; 
 void* get_can_dlc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,void*) ; 

__attribute__((used)) static void ican3_to_can_frame(struct ican3_dev *mod,
			       struct ican3_fast_desc *desc,
			       struct can_frame *cf)
{
	if ((desc->command & ICAN3_CAN_TYPE_MASK) == ICAN3_CAN_TYPE_SFF) {
		if (desc->data[1] & ICAN3_SFF_RTR)
			cf->can_id |= CAN_RTR_FLAG;

		cf->can_id |= desc->data[0] << 3;
		cf->can_id |= (desc->data[1] & 0xe0) >> 5;
		cf->can_dlc = get_can_dlc(desc->data[1] & ICAN3_CAN_DLC_MASK);
		memcpy(cf->data, &desc->data[2], cf->can_dlc);
	} else {
		cf->can_dlc = get_can_dlc(desc->data[0] & ICAN3_CAN_DLC_MASK);
		if (desc->data[0] & ICAN3_EFF_RTR)
			cf->can_id |= CAN_RTR_FLAG;

		if (desc->data[0] & ICAN3_EFF) {
			cf->can_id |= CAN_EFF_FLAG;
			cf->can_id |= desc->data[2] << 21; /* 28-21 */
			cf->can_id |= desc->data[3] << 13; /* 20-13 */
			cf->can_id |= desc->data[4] << 5;  /* 12-5  */
			cf->can_id |= (desc->data[5] & 0xf8) >> 3;
		} else {
			cf->can_id |= desc->data[2] << 3;  /* 10-3  */
			cf->can_id |= desc->data[3] >> 5;  /* 2-0   */
		}

		memcpy(cf->data, &desc->data[6], cf->can_dlc);
	}
}