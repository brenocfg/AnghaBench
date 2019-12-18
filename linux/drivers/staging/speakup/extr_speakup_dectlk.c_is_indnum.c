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
typedef  char u_char ;

/* Variables and functions */

__attribute__((used)) static int is_indnum(u_char *ch)
{
	if ((*ch >= '0') && (*ch <= '9')) {
		*ch = *ch - '0';
		return 1;
	}
	return 0;
}