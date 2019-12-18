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
struct intel_engine_cs {int class; } ;

/* Variables and functions */
#define  COPY_ENGINE_CLASS 131 
 int ENODEV ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
#define  RENDER_CLASS 130 
#define  VIDEO_DECODE_CLASS 129 
#define  VIDEO_ENHANCEMENT_CLASS 128 
 int /*<<< orphan*/  setup_bcs (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  setup_common (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  setup_rcs (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  setup_vcs (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  setup_vecs (struct intel_engine_cs*) ; 

int intel_ring_submission_setup(struct intel_engine_cs *engine)
{
	setup_common(engine);

	switch (engine->class) {
	case RENDER_CLASS:
		setup_rcs(engine);
		break;
	case VIDEO_DECODE_CLASS:
		setup_vcs(engine);
		break;
	case COPY_ENGINE_CLASS:
		setup_bcs(engine);
		break;
	case VIDEO_ENHANCEMENT_CLASS:
		setup_vecs(engine);
		break;
	default:
		MISSING_CASE(engine->class);
		return -ENODEV;
	}

	return 0;
}