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
typedef  int /*<<< orphan*/  u8 ;
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;
struct detailed_mode_closure {int modes; struct edid* edid; struct drm_connector* connector; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_cvt_mode ; 
 int /*<<< orphan*/  drm_for_each_detailed_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct detailed_mode_closure*) ; 
 scalar_t__ version_greater (struct edid*,int,int) ; 

__attribute__((used)) static int
add_cvt_modes(struct drm_connector *connector, struct edid *edid)
{	
	struct detailed_mode_closure closure = {
		.connector = connector,
		.edid = edid,
	};

	if (version_greater(edid, 1, 2))
		drm_for_each_detailed_block((u8 *)edid, do_cvt_mode, &closure);

	/* XXX should also look for CVT codes in VTB blocks */

	return closure.modes;
}