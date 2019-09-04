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
struct toptree {TYPE_1__* parent; } ;
struct TYPE_2__ {struct toptree* parent; } ;

/* Variables and functions */

__attribute__((used)) static struct toptree *core_book(struct toptree *core)
{
	return core->parent->parent;
}