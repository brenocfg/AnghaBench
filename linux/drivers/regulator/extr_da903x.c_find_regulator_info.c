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
struct TYPE_2__ {int id; } ;
struct da903x_regulator_info {TYPE_1__ desc; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct da903x_regulator_info*) ; 
 struct da903x_regulator_info* da903x_regulator_info ; 

__attribute__((used)) static inline struct da903x_regulator_info *find_regulator_info(int id)
{
	struct da903x_regulator_info *ri;
	int i;

	for (i = 0; i < ARRAY_SIZE(da903x_regulator_info); i++) {
		ri = &da903x_regulator_info[i];
		if (ri->desc.id == id)
			return ri;
	}
	return NULL;
}