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
struct uvc_video_chain {int dummy; } ;
struct TYPE_2__ {scalar_t__ prev; scalar_t__ next; } ;
struct uvc_entity {int /*<<< orphan*/  id; TYPE_1__ chain; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UVC_TRACE_DESCR ; 
 int /*<<< orphan*/  UVC_TRACE_PROBE ; 
 scalar_t__ uvc_scan_chain_backward (struct uvc_video_chain*,struct uvc_entity**) ; 
 scalar_t__ uvc_scan_chain_entity (struct uvc_video_chain*,struct uvc_entity*) ; 
 scalar_t__ uvc_scan_chain_forward (struct uvc_video_chain*,struct uvc_entity*,struct uvc_entity*) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int uvc_scan_chain(struct uvc_video_chain *chain,
			  struct uvc_entity *term)
{
	struct uvc_entity *entity, *prev;

	uvc_trace(UVC_TRACE_PROBE, "Scanning UVC chain:");

	entity = term;
	prev = NULL;

	while (entity != NULL) {
		/* Entity must not be part of an existing chain */
		if (entity->chain.next || entity->chain.prev) {
			uvc_trace(UVC_TRACE_DESCR, "Found reference to "
				"entity %d already in chain.\n", entity->id);
			return -EINVAL;
		}

		/* Process entity */
		if (uvc_scan_chain_entity(chain, entity) < 0)
			return -EINVAL;

		/* Forward scan */
		if (uvc_scan_chain_forward(chain, entity, prev) < 0)
			return -EINVAL;

		/* Backward scan */
		prev = entity;
		if (uvc_scan_chain_backward(chain, &entity) < 0)
			return -EINVAL;
	}

	return 0;
}