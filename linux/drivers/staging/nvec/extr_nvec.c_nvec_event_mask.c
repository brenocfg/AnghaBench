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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static void nvec_event_mask(char *ev, u32 mask)
{
	ev[3] = mask >> 16 & 0xff;
	ev[4] = mask >> 24 & 0xff;
	ev[5] = mask >> 0  & 0xff;
	ev[6] = mask >> 8  & 0xff;
}