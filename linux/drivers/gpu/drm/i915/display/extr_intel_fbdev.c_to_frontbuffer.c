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
struct intel_frontbuffer {int dummy; } ;
struct intel_fbdev {TYPE_1__* fb; } ;
struct TYPE_2__ {struct intel_frontbuffer* frontbuffer; } ;

/* Variables and functions */

__attribute__((used)) static struct intel_frontbuffer *to_frontbuffer(struct intel_fbdev *ifbdev)
{
	return ifbdev->fb->frontbuffer;
}