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
struct mxs_auart_port {TYPE_1__* vendor; } ;
struct TYPE_2__ {unsigned int* reg_offset; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int mxs_reg_to_offset(const struct mxs_auart_port *uap,
				      unsigned int reg)
{
	return uap->vendor->reg_offset[reg];
}