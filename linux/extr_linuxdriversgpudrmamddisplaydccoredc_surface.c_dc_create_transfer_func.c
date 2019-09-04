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
struct dc_transfer_func {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct dc_transfer_func* kvzalloc (int,int /*<<< orphan*/ ) ; 

struct dc_transfer_func *dc_create_transfer_func(void)
{
	struct dc_transfer_func *tf = kvzalloc(sizeof(*tf), GFP_KERNEL);

	if (tf == NULL)
		goto alloc_fail;

	kref_init(&tf->refcount);

	return tf;

alloc_fail:
	return NULL;
}