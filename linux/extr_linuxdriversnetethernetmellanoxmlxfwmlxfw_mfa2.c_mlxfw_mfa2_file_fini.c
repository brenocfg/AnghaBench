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
struct mlxfw_mfa2_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlxfw_mfa2_file*) ; 

void mlxfw_mfa2_file_fini(struct mlxfw_mfa2_file *mfa2_file)
{
	kfree(mfa2_file);
}