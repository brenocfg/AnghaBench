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
struct dc_plane_state {int /*<<< orphan*/  refcount; } ;
struct dc {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  construct (int /*<<< orphan*/ ,struct dc_plane_state*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct dc_plane_state* kvzalloc (int,int /*<<< orphan*/ ) ; 

struct dc_plane_state *dc_create_plane_state(struct dc *dc)
{
	struct dc *core_dc = dc;

	struct dc_plane_state *plane_state = kvzalloc(sizeof(*plane_state),
						      GFP_KERNEL);

	if (NULL == plane_state)
		return NULL;

	kref_init(&plane_state->refcount);
	construct(core_dc->ctx, plane_state);

	return plane_state;
}