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
struct uverbs_attr_bundle {int dummy; } ;
struct ib_counters {int dummy; } ;
struct mlx5_ib_mcounters {struct ib_counters ibcntrs; int /*<<< orphan*/  mcntrs_mutex; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct ib_counters* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mlx5_ib_mcounters* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ib_counters *mlx5_ib_create_counters(struct ib_device *device,
						   struct uverbs_attr_bundle *attrs)
{
	struct mlx5_ib_mcounters *mcounters;

	mcounters = kzalloc(sizeof(*mcounters), GFP_KERNEL);
	if (!mcounters)
		return ERR_PTR(-ENOMEM);

	mutex_init(&mcounters->mcntrs_mutex);

	return &mcounters->ibcntrs;
}