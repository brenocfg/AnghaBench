#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned short base; } ;
typedef  TYPE_1__ ppa_struct ;

/* Variables and functions */
 int /*<<< orphan*/  ppa_d_pulse (unsigned short,int) ; 

__attribute__((used)) static void ppa_disconnect(ppa_struct *dev)
{
	unsigned short ppb = dev->base;

	ppa_d_pulse(ppb, 0);
	ppa_d_pulse(ppb, 0x3c);
	ppa_d_pulse(ppb, 0x20);
	ppa_d_pulse(ppb, 0xf);
}