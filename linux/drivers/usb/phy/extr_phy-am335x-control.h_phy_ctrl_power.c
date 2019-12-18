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
struct phy_control {int /*<<< orphan*/  (* phy_power ) (struct phy_control*,int /*<<< orphan*/ ,int,int) ;} ;
typedef  enum usb_dr_mode { ____Placeholder_usb_dr_mode } usb_dr_mode ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct phy_control*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline void phy_ctrl_power(struct phy_control *phy_ctrl, u32 id,
				enum usb_dr_mode dr_mode, bool on)
{
	phy_ctrl->phy_power(phy_ctrl, id, dr_mode, on);
}