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
typedef  int u8 ;
struct ide_timing {int mode; } ;

/* Variables and functions */
 struct ide_timing* ide_timing ; 

struct ide_timing *ide_timing_find_mode(u8 speed)
{
	struct ide_timing *t;

	for (t = ide_timing; t->mode != speed; t++)
		if (t->mode == 0xff)
			return NULL;
	return t;
}