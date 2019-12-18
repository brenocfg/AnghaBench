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
struct ti_bandgap {TYPE_1__* regval; } ;
struct TYPE_2__ {void* data; } ;

/* Variables and functions */
 void* ERR_PTR (int) ; 
 int ti_bandgap_validate (struct ti_bandgap*,int) ; 

void *ti_bandgap_get_sensor_data(struct ti_bandgap *bgp, int id)
{
	int ret = ti_bandgap_validate(bgp, id);
	if (ret)
		return ERR_PTR(ret);

	return bgp->regval[id].data;
}