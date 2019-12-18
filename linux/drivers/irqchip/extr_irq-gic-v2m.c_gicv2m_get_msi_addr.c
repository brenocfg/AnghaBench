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
struct TYPE_2__ {int start; } ;
struct v2m_data {int flags; TYPE_1__ res; } ;
typedef  int phys_addr_t ;

/* Variables and functions */
 int GICV2M_GRAVITON_ADDRESS_ONLY ; 
 int V2M_MSI_SETSPI_NS ; 

__attribute__((used)) static phys_addr_t gicv2m_get_msi_addr(struct v2m_data *v2m, int hwirq)
{
	if (v2m->flags & GICV2M_GRAVITON_ADDRESS_ONLY)
		return v2m->res.start | ((hwirq - 32) << 3);
	else
		return v2m->res.start + V2M_MSI_SETSPI_NS;
}