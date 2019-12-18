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

unsigned ef4_mdio_id_oui(u32 id)
{
	unsigned oui = 0;
	int i;

	/* The bits of the OUI are designated a..x, with a=0 and b variable.
	 * In the id register c is the MSB but the OUI is conventionally
	 * written as bytes h..a, p..i, x..q.  Reorder the bits accordingly. */
	for (i = 0; i < 22; ++i)
		if (id & (1 << (i + 10)))
			oui |= 1 << (i ^ 7);

	return oui;
}