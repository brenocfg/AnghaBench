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

/* Variables and functions */
 int MLX5_IRQ_VEC_COMP_BASE ; 
 int /*<<< orphan*/  MLX5_MAX_IRQ_NAME ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void irq_set_name(char *name, int vecidx)
{
	if (vecidx == 0) {
		snprintf(name, MLX5_MAX_IRQ_NAME, "mlx5_async");
		return;
	}

	snprintf(name, MLX5_MAX_IRQ_NAME, "mlx5_comp%d",
		 vecidx - MLX5_IRQ_VEC_COMP_BASE);
	return;
}