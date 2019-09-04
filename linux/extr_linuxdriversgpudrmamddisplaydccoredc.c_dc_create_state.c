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
struct dc_state {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct dc_state* kzalloc (int,int /*<<< orphan*/ ) ; 

struct dc_state *dc_create_state(void)
{
	struct dc_state *context = kzalloc(sizeof(struct dc_state),
					   GFP_KERNEL);

	if (!context)
		return NULL;

	kref_init(&context->refcount);
	return context;
}