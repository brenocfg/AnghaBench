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
struct display_mode_lib {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dml; } ;
struct dc_state {int /*<<< orphan*/  refcount; TYPE_1__ bw_ctx; } ;
struct dc {int /*<<< orphan*/  dml; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct dc_state* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

struct dc_state *dc_create_state(struct dc *dc)
{
	struct dc_state *context = kvzalloc(sizeof(struct dc_state),
					    GFP_KERNEL);

	if (!context)
		return NULL;
	/* Each context must have their own instance of VBA and in order to
	 * initialize and obtain IP and SOC the base DML instance from DC is
	 * initially copied into every context
	 */
#ifdef CONFIG_DRM_AMD_DC_DCN1_0
	memcpy(&context->bw_ctx.dml, &dc->dml, sizeof(struct display_mode_lib));
#endif

	kref_init(&context->refcount);

	return context;
}