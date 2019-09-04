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
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  scanhex (unsigned long*) ; 
 int /*<<< orphan*/  xmon_set_pagination_lpp (unsigned long) ; 

__attribute__((used)) static void set_lpp_cmd(void)
{
	unsigned long lpp;

	if (!scanhex(&lpp)) {
		printf("Invalid number.\n");
		lpp = 0;
	}
	xmon_set_pagination_lpp(lpp);
}