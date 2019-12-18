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
struct ww_acquire_ctx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  n_coupled; } ;
struct regulator_dev {TYPE_1__ coupling_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  regulator_unlock_recursive (struct regulator_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ww_acquire_fini (struct ww_acquire_ctx*) ; 

__attribute__((used)) static void regulator_unlock_dependent(struct regulator_dev *rdev,
				       struct ww_acquire_ctx *ww_ctx)
{
	regulator_unlock_recursive(rdev, rdev->coupling_desc.n_coupled);
	ww_acquire_fini(ww_ctx);
}