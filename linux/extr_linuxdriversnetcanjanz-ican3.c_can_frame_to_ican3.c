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
struct ican3_fast_desc {int* data; int /*<<< orphan*/  command; } ;
struct TYPE_2__ {int ctrlmode; } ;
struct ican3_dev {TYPE_1__ can; } ;
struct can_frame {int can_dlc; int can_id; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int CAN_CTRLMODE_ONE_SHOT ; 
 int CAN_EFF_FLAG ; 
 int CAN_RTR_FLAG ; 
 int /*<<< orphan*/  ICAN3_CAN_TYPE_EFF ; 
 int ICAN3_ECHO ; 
 int ICAN3_EFF ; 
 int ICAN3_EFF_RTR ; 
 int ICAN3_SNGL ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void can_frame_to_ican3(struct ican3_dev *mod,
			       struct can_frame *cf,
			       struct ican3_fast_desc *desc)
{
	/* clear out any stale data in the descriptor */
	memset(desc->data, 0, sizeof(desc->data));

	/* we always use the extended format, with the ECHO flag set */
	desc->command = ICAN3_CAN_TYPE_EFF;
	desc->data[0] |= cf->can_dlc;
	desc->data[1] |= ICAN3_ECHO;

	/* support single transmission (no retries) mode */
	if (mod->can.ctrlmode & CAN_CTRLMODE_ONE_SHOT)
		desc->data[1] |= ICAN3_SNGL;

	if (cf->can_id & CAN_RTR_FLAG)
		desc->data[0] |= ICAN3_EFF_RTR;

	/* pack the id into the correct places */
	if (cf->can_id & CAN_EFF_FLAG) {
		desc->data[0] |= ICAN3_EFF;
		desc->data[2] = (cf->can_id & 0x1fe00000) >> 21; /* 28-21 */
		desc->data[3] = (cf->can_id & 0x001fe000) >> 13; /* 20-13 */
		desc->data[4] = (cf->can_id & 0x00001fe0) >> 5;  /* 12-5  */
		desc->data[5] = (cf->can_id & 0x0000001f) << 3;  /* 4-0   */
	} else {
		desc->data[2] = (cf->can_id & 0x7F8) >> 3; /* bits 10-3 */
		desc->data[3] = (cf->can_id & 0x007) << 5; /* bits 2-0  */
	}

	/* copy the data bits into the descriptor */
	memcpy(&desc->data[6], cf->data, cf->can_dlc);
}