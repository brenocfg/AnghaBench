#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ io_addr; } ;

/* Variables and functions */
 int inb_p (scalar_t__) ; 
 TYPE_1__ pcipcwd_private ; 

__attribute__((used)) static int pcipcwd_get_option_switches(void)
{
	int option_switches;

	option_switches = inb_p(pcipcwd_private.io_addr + 3);
	return option_switches;
}