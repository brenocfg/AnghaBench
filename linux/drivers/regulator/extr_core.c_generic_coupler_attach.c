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
struct TYPE_2__ {int n_coupled; } ;
struct regulator_dev {TYPE_1__ coupling_desc; } ;
struct regulator_coupler {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  rdev_err (struct regulator_dev*,char*) ; 

__attribute__((used)) static int generic_coupler_attach(struct regulator_coupler *coupler,
				  struct regulator_dev *rdev)
{
	if (rdev->coupling_desc.n_coupled > 2) {
		rdev_err(rdev,
			 "Voltage balancing for multiple regulator couples is unimplemented\n");
		return -EPERM;
	}

	return 0;
}