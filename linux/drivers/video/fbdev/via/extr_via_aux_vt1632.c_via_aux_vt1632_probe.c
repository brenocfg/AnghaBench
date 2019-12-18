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
struct via_aux_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  probe (struct via_aux_bus*,int) ; 

void via_aux_vt1632_probe(struct via_aux_bus *bus)
{
	u8 i;

	for (i = 0x08; i <= 0x0F; i++)
		probe(bus, i);
}