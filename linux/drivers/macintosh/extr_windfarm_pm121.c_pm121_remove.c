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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm121_events ; 
 int /*<<< orphan*/  wf_unregister_client (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pm121_remove(struct platform_device *ddev)
{
	wf_unregister_client(&pm121_events);
	return 0;
}