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
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int* bytes; } ;
struct CHIPSTATE {TYPE_1__ shadow; struct v4l2_subdev sd; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int chip_write (struct CHIPSTATE*,int,int) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,int) ; 

__attribute__((used)) static int chip_write_masked(struct CHIPSTATE *chip,
			     int subaddr, int val, int mask)
{
	struct v4l2_subdev *sd = &chip->sd;

	if (mask != 0) {
		if (subaddr < 0) {
			val = (chip->shadow.bytes[1] & ~mask) | (val & mask);
		} else {
			if (subaddr + 1 >= ARRAY_SIZE(chip->shadow.bytes)) {
				v4l2_info(sd,
					"Tried to access a non-existent register: %d\n",
					subaddr);
				return -EINVAL;
			}

			val = (chip->shadow.bytes[subaddr+1] & ~mask) | (val & mask);
		}
	}
	return chip_write(chip, subaddr, val);
}