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
struct controller {int dummy; } ;

/* Variables and functions */
 scalar_t__ pciehp_card_present (struct controller*) ; 
 scalar_t__ pciehp_check_link_active (struct controller*) ; 

bool pciehp_card_present_or_link_active(struct controller *ctrl)
{
	return pciehp_card_present(ctrl) || pciehp_check_link_active(ctrl);
}