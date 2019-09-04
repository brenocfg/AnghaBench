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
struct binder_ref {struct binder_ref* death; scalar_t__ node; } ;

/* Variables and functions */
 int /*<<< orphan*/  binder_free_node (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct binder_ref*) ; 

__attribute__((used)) static void binder_free_ref(struct binder_ref *ref)
{
	if (ref->node)
		binder_free_node(ref->node);
	kfree(ref->death);
	kfree(ref);
}