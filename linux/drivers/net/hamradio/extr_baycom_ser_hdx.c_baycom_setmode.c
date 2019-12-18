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
struct baycom_state {int opt_dcd; } ;

/* Variables and functions */
 scalar_t__ strchr (char const*,char) ; 

__attribute__((used)) static int baycom_setmode(struct baycom_state *bc, const char *modestr)
{
	if (strchr(modestr, '*'))
		bc->opt_dcd = 0;
	else if (strchr(modestr, '+'))
		bc->opt_dcd = -1;
	else if (strchr(modestr, '@'))
		bc->opt_dcd = -2;
	else
		bc->opt_dcd = 1;
	return 0;
}