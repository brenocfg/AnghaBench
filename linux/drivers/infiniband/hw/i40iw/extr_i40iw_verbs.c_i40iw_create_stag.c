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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct i40iw_device {int mr_stagmask; int max_mr; int /*<<< orphan*/  allocated_mrs; } ;
typedef  int /*<<< orphan*/  random ;

/* Variables and functions */
 int I40IW_CQPSQ_STAG_IDX_SHIFT ; 
 int /*<<< orphan*/  get_random_bytes (int*,int) ; 
 int /*<<< orphan*/  i40iw_add_devusecount (struct i40iw_device*) ; 
 int i40iw_alloc_resource (struct i40iw_device*,int /*<<< orphan*/ ,int,int*,int*) ; 

__attribute__((used)) static u32 i40iw_create_stag(struct i40iw_device *iwdev)
{
	u32 stag = 0;
	u32 stag_index = 0;
	u32 next_stag_index;
	u32 driver_key;
	u32 random;
	u8 consumer_key;
	int ret;

	get_random_bytes(&random, sizeof(random));
	consumer_key = (u8)random;

	driver_key = random & ~iwdev->mr_stagmask;
	next_stag_index = (random & iwdev->mr_stagmask) >> 8;
	next_stag_index %= iwdev->max_mr;

	ret = i40iw_alloc_resource(iwdev,
				   iwdev->allocated_mrs, iwdev->max_mr,
				   &stag_index, &next_stag_index);
	if (!ret) {
		stag = stag_index << I40IW_CQPSQ_STAG_IDX_SHIFT;
		stag |= driver_key;
		stag += (u32)consumer_key;
		i40iw_add_devusecount(iwdev);
	}
	return stag;
}