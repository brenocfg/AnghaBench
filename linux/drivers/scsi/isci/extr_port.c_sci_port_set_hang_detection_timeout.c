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
struct isci_port {int active_phy_mask; int hang_detect_users; TYPE_2__** phy_table; } ;
struct TYPE_4__ {TYPE_1__* link_layer_registers; } ;
struct TYPE_3__ {int /*<<< orphan*/  link_layer_hang_detection_timeout; } ;

/* Variables and functions */
 int SCI_MAX_PHYS ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

void sci_port_set_hang_detection_timeout(struct isci_port *iport, u32 timeout)
{
	int phy_index;
	u32 phy_mask = iport->active_phy_mask;

	if (timeout)
		++iport->hang_detect_users;
	else if (iport->hang_detect_users > 1)
		--iport->hang_detect_users;
	else
		iport->hang_detect_users = 0;

	if (timeout || (iport->hang_detect_users == 0)) {
		for (phy_index = 0; phy_index < SCI_MAX_PHYS; phy_index++) {
			if ((phy_mask >> phy_index) & 1) {
				writel(timeout,
				       &iport->phy_table[phy_index]
					  ->link_layer_registers
					  ->link_layer_hang_detection_timeout);
			}
		}
	}
}