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
struct dlfb_data {scalar_t__ damage_y2; void* damage_y; scalar_t__ damage_x2; void* damage_x; } ;

/* Variables and functions */
 void* INT_MAX ; 

__attribute__((used)) static void dlfb_init_damage(struct dlfb_data *dlfb)
{
	dlfb->damage_x = INT_MAX;
	dlfb->damage_x2 = 0;
	dlfb->damage_y = INT_MAX;
	dlfb->damage_y2 = 0;
}