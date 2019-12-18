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
 int /*<<< orphan*/  nv_tco_cleanup () ; 
 scalar_t__ tcobase ; 

__attribute__((used)) static int nv_tco_remove(struct platform_device *dev)
{
	if (tcobase)
		nv_tco_cleanup();

	return 0;
}