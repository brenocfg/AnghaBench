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
typedef  int /*<<< orphan*/  u32 ;
struct e1000_hw {int mac_type; int /*<<< orphan*/  ledctl_mode1; int /*<<< orphan*/  media_type; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  E1000_CTRL_SWDPIN0 ; 
 int /*<<< orphan*/  E1000_CTRL_SWDPIO0 ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  LEDCTL ; 
#define  e1000_82542_rev2_0 131 
#define  e1000_82542_rev2_1 130 
#define  e1000_82543 129 
#define  e1000_82544 128 
 int /*<<< orphan*/  e1000_media_type_copper ; 
 int /*<<< orphan*/  e1000_media_type_fiber ; 
 int /*<<< orphan*/  er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s32 e1000_led_off(struct e1000_hw *hw)
{
	u32 ctrl = er32(CTRL);

	switch (hw->mac_type) {
	case e1000_82542_rev2_0:
	case e1000_82542_rev2_1:
	case e1000_82543:
		/* Clear SW Defineable Pin 0 to turn off the LED */
		ctrl &= ~E1000_CTRL_SWDPIN0;
		ctrl |= E1000_CTRL_SWDPIO0;
		break;
	case e1000_82544:
		if (hw->media_type == e1000_media_type_fiber) {
			/* Clear SW Defineable Pin 0 to turn off the LED */
			ctrl &= ~E1000_CTRL_SWDPIN0;
			ctrl |= E1000_CTRL_SWDPIO0;
		} else {
			/* Set SW Defineable Pin 0 to turn off the LED */
			ctrl |= E1000_CTRL_SWDPIN0;
			ctrl |= E1000_CTRL_SWDPIO0;
		}
		break;
	default:
		if (hw->media_type == e1000_media_type_fiber) {
			/* Set SW Defineable Pin 0 to turn off the LED */
			ctrl |= E1000_CTRL_SWDPIN0;
			ctrl |= E1000_CTRL_SWDPIO0;
		} else if (hw->media_type == e1000_media_type_copper) {
			ew32(LEDCTL, hw->ledctl_mode1);
			return E1000_SUCCESS;
		}
		break;
	}

	ew32(CTRL, ctrl);

	return E1000_SUCCESS;
}