#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* state; } ;
struct intel_connector {TYPE_3__* encoder; TYPE_2__ base; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_6__ {int /*<<< orphan*/  (* get_hw_state ) (TYPE_3__*,int*) ;} ;
struct TYPE_4__ {scalar_t__ crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*,int*) ; 

__attribute__((used)) static bool intel_dp_mst_get_hw_state(struct intel_connector *connector)
{
	if (connector->encoder && connector->base.state->crtc) {
		enum pipe pipe;
		if (!connector->encoder->get_hw_state(connector->encoder, &pipe))
			return false;
		return true;
	}
	return false;
}