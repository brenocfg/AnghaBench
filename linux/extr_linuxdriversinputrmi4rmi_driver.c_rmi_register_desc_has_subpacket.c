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
typedef  scalar_t__ u8 ;
struct rmi_register_desc_item {int /*<<< orphan*/  subpacket_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  RMI_REG_DESC_PRESENSE_BITS ; 
 scalar_t__ find_next_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

bool rmi_register_desc_has_subpacket(const struct rmi_register_desc_item *item,
	u8 subpacket)
{
	return find_next_bit(item->subpacket_map, RMI_REG_DESC_PRESENSE_BITS,
				subpacket) == subpacket;
}