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
struct rtw_regulatory {int /*<<< orphan*/  alpha2; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct rtw_regulatory*) ; 
 struct rtw_regulatory* all_chplan_map ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 
 struct rtw_regulatory rtw_defined_chplan ; 

__attribute__((used)) static struct rtw_regulatory rtw_regd_find_reg_by_name(char *alpha2)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(all_chplan_map); i++) {
		if (!memcmp(all_chplan_map[i].alpha2, alpha2, 2))
			return all_chplan_map[i];
	}

	return rtw_defined_chplan;
}