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
struct recurse_struct {void* obj; int (* fn ) (struct device*,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  descend_children ; 
 int device_for_each_child (int /*<<< orphan*/ *,struct recurse_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  root ; 

__attribute__((used)) static int for_each_padev(int (*fn)(struct device *, void *), void * data)
{
	struct recurse_struct recurse_data = {
		.obj	= data,
		.fn	= fn,
	};
	return device_for_each_child(&root, &recurse_data, descend_children);
}