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
struct enetc_mac_filter {int /*<<< orphan*/  mac_hash_table; scalar_t__ mac_addr_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENETC_MADDR_HASH_TBL_SZ ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enetc_reset_mac_addr_filter(struct enetc_mac_filter *filter)
{
	filter->mac_addr_cnt = 0;

	bitmap_zero(filter->mac_hash_table,
		    ENETC_MADDR_HASH_TBL_SZ);
}