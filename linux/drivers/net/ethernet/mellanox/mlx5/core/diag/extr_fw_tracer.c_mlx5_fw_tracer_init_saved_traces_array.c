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
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ saved_traces_index; } ;
struct mlx5_fw_tracer {TYPE_1__ st_arr; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlx5_fw_tracer_init_saved_traces_array(struct mlx5_fw_tracer *tracer)
{
	tracer->st_arr.saved_traces_index = 0;
	mutex_init(&tracer->st_arr.lock);
}