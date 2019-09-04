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
struct eeh_pe {int addr; } ;

/* Variables and functions */

__attribute__((used)) static int pnv_eeh_get_pe_addr(struct eeh_pe *pe)
{
	return pe->addr;
}