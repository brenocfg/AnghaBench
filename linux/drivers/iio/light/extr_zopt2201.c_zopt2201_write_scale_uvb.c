#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct zopt2201_data {int dummy; } ;
struct TYPE_3__ {int scale; int uscale; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* zopt2201_scale_uvb ; 
 int zopt2201_write_scale_uvb_by_idx (struct zopt2201_data*,int) ; 

__attribute__((used)) static int zopt2201_write_scale_uvb(struct zopt2201_data *data,
				     int val, int val2)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(zopt2201_scale_uvb); i++)
		if (val == zopt2201_scale_uvb[i].scale &&
		    val2 == zopt2201_scale_uvb[i].uscale)
			return zopt2201_write_scale_uvb_by_idx(data, i);

	return -EINVAL;
}