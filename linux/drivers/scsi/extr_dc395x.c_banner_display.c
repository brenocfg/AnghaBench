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

/* Variables and functions */
 int /*<<< orphan*/  DC395X_BANNER ; 
 int /*<<< orphan*/  DC395X_VERSION ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  dprintkl (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void banner_display(void)
{
	static int banner_done = 0;
	if (!banner_done)
	{
		dprintkl(KERN_INFO, "%s %s\n", DC395X_BANNER, DC395X_VERSION);
		banner_done = 1;
	}
}