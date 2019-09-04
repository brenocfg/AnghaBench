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
struct mdesc_handle {unsigned int handle_size; int /*<<< orphan*/  refcnt; void* self_base; int /*<<< orphan*/  list; int /*<<< orphan*/  mdesc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (unsigned long) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct mdesc_handle*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mdesc_handle_init(struct mdesc_handle *hp,
			      unsigned int handle_size,
			      void *base)
{
	BUG_ON(((unsigned long)&hp->mdesc) & (16UL - 1));

	memset(hp, 0, handle_size);
	INIT_LIST_HEAD(&hp->list);
	hp->self_base = base;
	refcount_set(&hp->refcnt, 1);
	hp->handle_size = handle_size;
}