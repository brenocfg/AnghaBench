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

/* Variables and functions */
 scalar_t__ core_has_mismatch_brps () ; 
 int get_num_brp_resources () ; 

__attribute__((used)) static int get_num_brps(void)
{
	int brps = get_num_brp_resources();
	return core_has_mismatch_brps() ? brps - 1 : brps;
}