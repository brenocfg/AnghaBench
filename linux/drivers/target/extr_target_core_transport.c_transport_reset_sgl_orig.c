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
struct se_cmd {scalar_t__ t_data_nents_orig; scalar_t__ t_data_nents; int /*<<< orphan*/ * t_data_sg_orig; int /*<<< orphan*/ * t_data_sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void transport_reset_sgl_orig(struct se_cmd *cmd)
{
	/*
	 * Check for saved t_data_sg that may be used for COMPARE_AND_WRITE
	 * emulation, and free + reset pointers if necessary..
	 */
	if (!cmd->t_data_sg_orig)
		return;

	kfree(cmd->t_data_sg);
	cmd->t_data_sg = cmd->t_data_sg_orig;
	cmd->t_data_sg_orig = NULL;
	cmd->t_data_nents = cmd->t_data_nents_orig;
	cmd->t_data_nents_orig = 0;
}