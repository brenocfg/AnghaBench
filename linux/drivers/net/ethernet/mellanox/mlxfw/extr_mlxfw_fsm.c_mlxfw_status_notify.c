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
typedef  int /*<<< orphan*/  u32 ;
struct mlxfw_dev {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* status_notify ) (struct mlxfw_dev*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mlxfw_dev*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxfw_status_notify(struct mlxfw_dev *mlxfw_dev,
				const char *msg, const char *comp_name,
				u32 done_bytes, u32 total_bytes)
{
	if (!mlxfw_dev->ops->status_notify)
		return;
	mlxfw_dev->ops->status_notify(mlxfw_dev, msg, comp_name,
				      done_bytes, total_bytes);
}