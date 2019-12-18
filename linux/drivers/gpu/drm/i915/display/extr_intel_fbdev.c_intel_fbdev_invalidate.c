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
struct intel_fbdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ORIGIN_CPU ; 
 int /*<<< orphan*/  intel_frontbuffer_invalidate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_frontbuffer (struct intel_fbdev*) ; 

__attribute__((used)) static void intel_fbdev_invalidate(struct intel_fbdev *ifbdev)
{
	intel_frontbuffer_invalidate(to_frontbuffer(ifbdev), ORIGIN_CPU);
}