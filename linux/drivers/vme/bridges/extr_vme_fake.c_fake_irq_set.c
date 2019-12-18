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
struct vme_bridge {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void fake_irq_set(struct vme_bridge *fake_bridge, int level,
		int state, int sync)
{
	/* Nothing to do */
}