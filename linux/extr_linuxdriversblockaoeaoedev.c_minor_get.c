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
typedef  int /*<<< orphan*/  ulong ;

/* Variables and functions */
 scalar_t__ aoe_dyndevs ; 
 int minor_get_dyn (int /*<<< orphan*/ *) ; 
 int minor_get_static (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
minor_get(ulong *sysminor, ulong aoemaj, int aoemin)
{
	if (aoe_dyndevs)
		return minor_get_dyn(sysminor);
	else
		return minor_get_static(sysminor, aoemaj, aoemin);
}