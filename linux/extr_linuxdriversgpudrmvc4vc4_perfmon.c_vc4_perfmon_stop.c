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
struct vc4_perfmon {unsigned int ncounters; int /*<<< orphan*/ * counters; } ;
struct vc4_dev {struct vc4_perfmon* active_perfmon; } ;

/* Variables and functions */
 int /*<<< orphan*/  V3D_PCTR (unsigned int) ; 
 int /*<<< orphan*/  V3D_PCTRE ; 
 scalar_t__ V3D_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V3D_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 

void vc4_perfmon_stop(struct vc4_dev *vc4, struct vc4_perfmon *perfmon,
		      bool capture)
{
	unsigned int i;

	if (WARN_ON_ONCE(!vc4->active_perfmon ||
			 perfmon != vc4->active_perfmon))
		return;

	if (capture) {
		for (i = 0; i < perfmon->ncounters; i++)
			perfmon->counters[i] += V3D_READ(V3D_PCTR(i));
	}

	V3D_WRITE(V3D_PCTRE, 0);
	vc4->active_perfmon = NULL;
}