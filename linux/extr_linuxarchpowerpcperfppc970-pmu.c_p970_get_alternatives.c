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
typedef  int u64 ;

/* Variables and functions */

__attribute__((used)) static int p970_get_alternatives(u64 event, unsigned int flags, u64 alt[])
{
	alt[0] = event;

	/* 2 alternatives for LSU empty */
	if (event == 0x2002 || event == 0x3002) {
		alt[1] = event ^ 0x1000;
		return 2;
	}

	return 1;
}