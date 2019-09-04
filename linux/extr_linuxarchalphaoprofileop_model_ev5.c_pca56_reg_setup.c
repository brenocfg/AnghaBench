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
struct op_system_config {int dummy; } ;
struct op_register_config {int dummy; } ;
struct op_counter_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  common_reg_setup (struct op_register_config*,struct op_counter_config*,struct op_system_config*,int,int) ; 

__attribute__((used)) static void
pca56_reg_setup(struct op_register_config *reg,
	        struct op_counter_config *ctr,
	        struct op_system_config *sys)
{
	common_reg_setup(reg, ctr, sys, 8, 11);
}