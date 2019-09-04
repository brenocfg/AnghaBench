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
struct resource {int dummy; } ;
struct TYPE_2__ {struct resource pcie_io_aperture; } ;

/* Variables and functions */
 TYPE_1__ mbus_state ; 

void mvebu_mbus_get_pcie_io_aperture(struct resource *res)
{
	if (!res)
		return;
	*res = mbus_state.pcie_io_aperture;
}