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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {scalar_t__ pipe; TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ HAS_IPS (int /*<<< orphan*/ ) ; 
 scalar_t__ PIPE_A ; 
 int /*<<< orphan*/  to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool hsw_crtc_supports_ips(struct intel_crtc *crtc)
{
	return HAS_IPS(to_i915(crtc->base.dev)) && crtc->pipe == PIPE_A;
}