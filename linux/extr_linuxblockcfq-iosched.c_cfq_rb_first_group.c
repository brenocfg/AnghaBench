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
struct cfq_rb_root {int /*<<< orphan*/  rb; } ;
struct cfq_group {int dummy; } ;

/* Variables and functions */
 struct cfq_group* rb_entry_cfqg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_first_cached (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct cfq_group *cfq_rb_first_group(struct cfq_rb_root *root)
{
	return rb_entry_cfqg(rb_first_cached(&root->rb));
}