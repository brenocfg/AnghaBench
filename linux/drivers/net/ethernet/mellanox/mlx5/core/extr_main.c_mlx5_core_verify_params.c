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
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_DEFAULT_PROF ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ prof_sel ; 
 int /*<<< orphan*/  profile ; 

__attribute__((used)) static void mlx5_core_verify_params(void)
{
	if (prof_sel >= ARRAY_SIZE(profile)) {
		pr_warn("mlx5_core: WARNING: Invalid module parameter prof_sel %d, valid range 0-%zu, changing back to default(%d)\n",
			prof_sel,
			ARRAY_SIZE(profile) - 1,
			MLX5_DEFAULT_PROF);
		prof_sel = MLX5_DEFAULT_PROF;
	}
}