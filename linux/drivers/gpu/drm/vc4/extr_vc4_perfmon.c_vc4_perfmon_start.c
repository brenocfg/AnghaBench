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
typedef  int u32 ;
struct vc4_perfmon {unsigned int ncounters; int* events; } ;
struct vc4_dev {struct vc4_perfmon* active_perfmon; } ;

/* Variables and functions */
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V3D_PCTRC ; 
 int /*<<< orphan*/  V3D_PCTRE ; 
 int V3D_PCTRE_EN ; 
 int /*<<< orphan*/  V3D_PCTRS (unsigned int) ; 
 int /*<<< orphan*/  V3D_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 

void vc4_perfmon_start(struct vc4_dev *vc4, struct vc4_perfmon *perfmon)
{
	unsigned int i;
	u32 mask;

	if (WARN_ON_ONCE(!perfmon || vc4->active_perfmon))
		return;

	for (i = 0; i < perfmon->ncounters; i++)
		V3D_WRITE(V3D_PCTRS(i), perfmon->events[i]);

	mask = GENMASK(perfmon->ncounters - 1, 0);
	V3D_WRITE(V3D_PCTRC, mask);
	V3D_WRITE(V3D_PCTRE, V3D_PCTRE_EN | mask);
	vc4->active_perfmon = perfmon;
}