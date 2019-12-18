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
struct TYPE_2__ {int n_coupled; int /*<<< orphan*/  coupler; int /*<<< orphan*/  n_resolved; struct regulator_dev** coupled_rdevs; } ;
struct regulator_dev {TYPE_1__ coupling_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct regulator_dev** kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_check_coupling_data (struct regulator_dev*) ; 
 int of_get_n_coupled (struct regulator_dev*) ; 
 int /*<<< orphan*/  rdev_err (struct regulator_dev*,char*,int) ; 
 int /*<<< orphan*/  regulator_find_coupler (struct regulator_dev*) ; 

__attribute__((used)) static int regulator_init_coupling(struct regulator_dev *rdev)
{
	int err, n_phandles;
	size_t alloc_size;

	if (!IS_ENABLED(CONFIG_OF))
		n_phandles = 0;
	else
		n_phandles = of_get_n_coupled(rdev);

	alloc_size = sizeof(*rdev) * (n_phandles + 1);

	rdev->coupling_desc.coupled_rdevs = kzalloc(alloc_size, GFP_KERNEL);
	if (!rdev->coupling_desc.coupled_rdevs)
		return -ENOMEM;

	/*
	 * Every regulator should always have coupling descriptor filled with
	 * at least pointer to itself.
	 */
	rdev->coupling_desc.coupled_rdevs[0] = rdev;
	rdev->coupling_desc.n_coupled = n_phandles + 1;
	rdev->coupling_desc.n_resolved++;

	/* regulator isn't coupled */
	if (n_phandles == 0)
		return 0;

	if (!of_check_coupling_data(rdev))
		return -EPERM;

	rdev->coupling_desc.coupler = regulator_find_coupler(rdev);
	if (IS_ERR(rdev->coupling_desc.coupler)) {
		err = PTR_ERR(rdev->coupling_desc.coupler);
		rdev_err(rdev, "failed to get coupler: %d\n", err);
		return err;
	}

	return 0;
}