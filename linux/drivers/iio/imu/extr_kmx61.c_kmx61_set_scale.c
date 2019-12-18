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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct kmx61_data {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int EINVAL ; 
 int KMX61_ACC ; 
 int /*<<< orphan*/  KMX61_ALL_STBY ; 
 int KMX61_MAG ; 
 int kmx61_get_mode (struct kmx61_data*,int /*<<< orphan*/ *,int) ; 
 int kmx61_set_mode (struct kmx61_data*,int /*<<< orphan*/ ,int,int) ; 
 int kmx61_set_range (struct kmx61_data*,int) ; 
 scalar_t__* kmx61_uscale_table ; 

__attribute__((used)) static int kmx61_set_scale(struct kmx61_data *data, u16 uscale)
{
	int ret, i;
	u8  mode;

	for (i = 0; i < ARRAY_SIZE(kmx61_uscale_table); i++) {
		if (kmx61_uscale_table[i] == uscale) {
			ret = kmx61_get_mode(data, &mode,
					     KMX61_ACC | KMX61_MAG);
			if (ret < 0)
				return ret;

			ret = kmx61_set_mode(data, KMX61_ALL_STBY,
					     KMX61_ACC | KMX61_MAG, true);
			if (ret < 0)
				return ret;

			ret = kmx61_set_range(data, i);
			if (ret < 0)
				return ret;

			return  kmx61_set_mode(data, mode,
					       KMX61_ACC | KMX61_MAG, true);
		}
	}
	return -EINVAL;
}