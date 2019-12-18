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
struct pci_func {int* config_space; } ;

/* Variables and functions */

__attribute__((used)) static int is_bridge(struct pci_func *func)
{
	/* Check the header type */
	if (((func->config_space[0x03] >> 16) & 0xFF) == 0x01)
		return 1;
	else
		return 0;
}