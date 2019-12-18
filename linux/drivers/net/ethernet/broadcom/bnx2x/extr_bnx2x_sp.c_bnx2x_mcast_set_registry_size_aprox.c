#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int num_bins_set; } ;
struct TYPE_4__ {TYPE_1__ aprox_match; } ;
struct bnx2x_mcast_obj {TYPE_2__ registry; } ;

/* Variables and functions */

__attribute__((used)) static void bnx2x_mcast_set_registry_size_aprox(struct bnx2x_mcast_obj *o,
						int n)
{
	o->registry.aprox_match.num_bins_set = n;
}