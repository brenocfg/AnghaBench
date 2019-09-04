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
struct ad5064_state {TYPE_1__* chip_info; } ;
struct TYPE_2__ {scalar_t__ shared_vref; } ;

/* Variables and functions */
 char const* const* ad5064_vref_names ; 

__attribute__((used)) static const char * const ad5064_vref_name(struct ad5064_state *st,
	unsigned int vref)
{
	return st->chip_info->shared_vref ? "vref" : ad5064_vref_names[vref];
}