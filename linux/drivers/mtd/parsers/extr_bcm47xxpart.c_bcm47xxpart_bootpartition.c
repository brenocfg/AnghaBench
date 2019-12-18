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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ bcm47xx_nvram_getenv (char*,char*,int) ; 
 int /*<<< orphan*/  kstrtoint (char*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int bcm47xxpart_bootpartition(void)
{
	char buf[4];
	int bootpartition;

	/* Check CFE environment variable */
	if (bcm47xx_nvram_getenv("bootpartition", buf, sizeof(buf)) > 0) {
		if (!kstrtoint(buf, 0, &bootpartition))
			return bootpartition;
	}

	return 0;
}