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
struct ad5449 {TYPE_1__* chip_info; } ;
struct TYPE_2__ {int num_channels; } ;

/* Variables and functions */

__attribute__((used)) static const char *ad5449_vref_name(struct ad5449 *st, int n)
{
	if (st->chip_info->num_channels == 1)
		return "VREF";

	if (n == 0)
		return "VREFA";
	else
		return "VREFB";
}