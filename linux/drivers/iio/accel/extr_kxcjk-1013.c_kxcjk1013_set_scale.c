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
struct kxcjk1013_data {int dummy; } ;
typedef  enum kxcjk1013_mode { ____Placeholder_kxcjk1013_mode } kxcjk1013_mode ;
struct TYPE_3__ {int scale; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* KXCJK1013_scale_table ; 
 int OPERATION ; 
 int STANDBY ; 
 int kxcjk1013_get_mode (struct kxcjk1013_data*,int*) ; 
 int kxcjk1013_set_mode (struct kxcjk1013_data*,int) ; 
 int kxcjk1013_set_range (struct kxcjk1013_data*,int) ; 

__attribute__((used)) static int kxcjk1013_set_scale(struct kxcjk1013_data *data, int val)
{
	int ret, i;
	enum kxcjk1013_mode store_mode;

	for (i = 0; i < ARRAY_SIZE(KXCJK1013_scale_table); ++i) {
		if (KXCJK1013_scale_table[i].scale == val) {
			ret = kxcjk1013_get_mode(data, &store_mode);
			if (ret < 0)
				return ret;

			ret = kxcjk1013_set_mode(data, STANDBY);
			if (ret < 0)
				return ret;

			ret = kxcjk1013_set_range(data, i);
			if (ret < 0)
				return ret;

			if (store_mode == OPERATION) {
				ret = kxcjk1013_set_mode(data, OPERATION);
				if (ret)
					return ret;
			}

			return 0;
		}
	}

	return -EINVAL;
}