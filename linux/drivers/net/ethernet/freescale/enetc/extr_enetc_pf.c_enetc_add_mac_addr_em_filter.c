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
struct enetc_mac_filter {int /*<<< orphan*/  mac_addr_cnt; int /*<<< orphan*/  mac_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,unsigned char const*) ; 

__attribute__((used)) static void enetc_add_mac_addr_em_filter(struct enetc_mac_filter *filter,
					 const unsigned char *addr)
{
	/* add exact match addr */
	ether_addr_copy(filter->mac_addr, addr);
	filter->mac_addr_cnt++;
}