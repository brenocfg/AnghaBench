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
typedef  int u8 ;
typedef  int u32 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int CONTINIOUS_REMOTE_UPDATE_SUPPORT_MASK ; 
 int CONTINIOUS_REMOTE_UPDATE_SUPPORT_SHIFT ; 
 int /*<<< orphan*/  GENERAL_CONFIG ; 
 int POWER_MANAGEMENT_MASK ; 
 int POWER_MANAGEMENT_SHIFT ; 
 int /*<<< orphan*/  VERIFY_CAP_REMOTE_PHY ; 
 int /*<<< orphan*/  read_8051_config (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void read_vc_remote_phy(struct hfi1_devdata *dd, u8 *power_management,
			       u8 *continuous)
{
	u32 frame;

	read_8051_config(dd, VERIFY_CAP_REMOTE_PHY, GENERAL_CONFIG, &frame);
	*power_management = (frame >> POWER_MANAGEMENT_SHIFT)
					& POWER_MANAGEMENT_MASK;
	*continuous = (frame >> CONTINIOUS_REMOTE_UPDATE_SUPPORT_SHIFT)
					& CONTINIOUS_REMOTE_UPDATE_SUPPORT_MASK;
}