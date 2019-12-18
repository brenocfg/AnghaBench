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
struct da9055_regulator_info {TYPE_1__ reg_desc; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct da9055_regulator_info*) ; 
 struct da9055_regulator_info* da9055_regulator_info ; 

__attribute__((used)) static inline struct da9055_regulator_info *find_regulator_info(int id)
{
	struct da9055_regulator_info *info;
	int i;

	for (i = 0; i < ARRAY_SIZE(da9055_regulator_info); i++) {
		info = &da9055_regulator_info[i];
		if (info->reg_desc.id == id)
			return info;
	}

	return NULL;
}