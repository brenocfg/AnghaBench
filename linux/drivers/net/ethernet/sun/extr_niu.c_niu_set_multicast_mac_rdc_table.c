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
struct niu {int dummy; } ;

/* Variables and functions */
 int __set_rdc_table_num (struct niu*,int,int,int,int) ; 

__attribute__((used)) static int niu_set_multicast_mac_rdc_table(struct niu *np, int table_num,
					   int mac_pref)
{
	return __set_rdc_table_num(np, 16, 8, table_num, mac_pref);
}