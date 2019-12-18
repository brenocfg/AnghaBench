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
struct mod_freesync {int dummy; } ;
struct dc {int dummy; } ;
struct core_freesync {struct mod_freesync public; struct dc* dc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct core_freesync*) ; 
 struct core_freesync* kzalloc (int,int /*<<< orphan*/ ) ; 

struct mod_freesync *mod_freesync_create(struct dc *dc)
{
	struct core_freesync *core_freesync =
			kzalloc(sizeof(struct core_freesync), GFP_KERNEL);

	if (core_freesync == NULL)
		goto fail_alloc_context;

	if (dc == NULL)
		goto fail_construct;

	core_freesync->dc = dc;
	return &core_freesync->public;

fail_construct:
	kfree(core_freesync);

fail_alloc_context:
	return NULL;
}