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
struct nv50_devinit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pmu_load (struct nv50_devinit*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
gm200_devinit_preos(struct nv50_devinit *init, bool post)
{
	/* Optional: Execute PRE_OS application on PMU, which should at
	 * least take care of fans until a full PMU has been loaded.
	 */
	pmu_load(init, 0x01, post, NULL, NULL);
}