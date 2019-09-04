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
struct lis3lv02d {int regs_size; int /*<<< orphan*/ * reg_cache; int /*<<< orphan*/ * regs; int /*<<< orphan*/  (* write ) (struct lis3lv02d*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ regs_stored; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct lis3lv02d*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void lis3_context_restore(struct lis3lv02d *lis3)
{
	int i;
	if (lis3->regs_stored)
		for (i = 0; i < lis3->regs_size; i++)
			lis3->write(lis3, lis3->regs[i], lis3->reg_cache[i]);
}