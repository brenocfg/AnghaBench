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
struct mma8452_data {TYPE_1__* chip_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  mma_scales; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int mma8452_get_int_plus_micros_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mma8452_get_scale_index(struct mma8452_data *data, int val, int val2)
{
	return mma8452_get_int_plus_micros_index(data->chip_info->mma_scales,
			ARRAY_SIZE(data->chip_info->mma_scales), val, val2);
}