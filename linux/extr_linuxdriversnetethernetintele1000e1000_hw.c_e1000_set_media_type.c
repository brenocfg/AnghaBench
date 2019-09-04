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
typedef  int u32 ;
struct e1000_hw {scalar_t__ mac_type; int tbi_compatibility_en; int device_id; void* media_type; } ;

/* Variables and functions */
#define  E1000_DEV_ID_82545GM_SERDES 132 
#define  E1000_DEV_ID_82546GB_SERDES 131 
 int E1000_STATUS_TBIMODE ; 
 int /*<<< orphan*/  STATUS ; 
#define  e1000_82542_rev2_0 130 
#define  e1000_82542_rev2_1 129 
 scalar_t__ e1000_82543 ; 
#define  e1000_ce4100 128 
 void* e1000_media_type_copper ; 
 void* e1000_media_type_fiber ; 
 void* e1000_media_type_internal_serdes ; 
 int er32 (int /*<<< orphan*/ ) ; 

void e1000_set_media_type(struct e1000_hw *hw)
{
	u32 status;

	if (hw->mac_type != e1000_82543) {
		/* tbi_compatibility is only valid on 82543 */
		hw->tbi_compatibility_en = false;
	}

	switch (hw->device_id) {
	case E1000_DEV_ID_82545GM_SERDES:
	case E1000_DEV_ID_82546GB_SERDES:
		hw->media_type = e1000_media_type_internal_serdes;
		break;
	default:
		switch (hw->mac_type) {
		case e1000_82542_rev2_0:
		case e1000_82542_rev2_1:
			hw->media_type = e1000_media_type_fiber;
			break;
		case e1000_ce4100:
			hw->media_type = e1000_media_type_copper;
			break;
		default:
			status = er32(STATUS);
			if (status & E1000_STATUS_TBIMODE) {
				hw->media_type = e1000_media_type_fiber;
				/* tbi_compatibility not valid on fiber */
				hw->tbi_compatibility_en = false;
			} else {
				hw->media_type = e1000_media_type_copper;
			}
			break;
		}
	}
}