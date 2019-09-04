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
struct gameport {int dummy; } ;

/* Variables and functions */
#define  GAMEPORT_MODE_RAW 128 

__attribute__((used)) static int fm801_gp_open(struct gameport *gameport, int mode)
{
	switch (mode) {
#ifdef HAVE_COOKED
	case GAMEPORT_MODE_COOKED:
		return 0;
#endif
	case GAMEPORT_MODE_RAW:
		return 0;
	default:
		return -1;
	}

	return 0;
}