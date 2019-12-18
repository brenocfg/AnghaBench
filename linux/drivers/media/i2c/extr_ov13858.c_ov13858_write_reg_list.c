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
struct ov13858_reg_list {int /*<<< orphan*/  num_of_regs; int /*<<< orphan*/  regs; } ;
struct ov13858 {int dummy; } ;

/* Variables and functions */
 int ov13858_write_regs (struct ov13858*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov13858_write_reg_list(struct ov13858 *ov13858,
				  const struct ov13858_reg_list *r_list)
{
	return ov13858_write_regs(ov13858, r_list->regs, r_list->num_of_regs);
}