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
struct mvumi_tag {size_t top; unsigned short* stack; } ;
struct mvumi_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static unsigned short tag_get_one(struct mvumi_hba *mhba, struct mvumi_tag *st)
{
	BUG_ON(st->top <= 0);
	return st->stack[--st->top];
}