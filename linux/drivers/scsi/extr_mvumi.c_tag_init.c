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
struct mvumi_tag {unsigned short size; unsigned short top; unsigned short* stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static void tag_init(struct mvumi_tag *st, unsigned short size)
{
	unsigned short i;
	BUG_ON(size != st->size);
	st->top = size;
	for (i = 0; i < size; i++)
		st->stack[i] = size - 1 - i;
}