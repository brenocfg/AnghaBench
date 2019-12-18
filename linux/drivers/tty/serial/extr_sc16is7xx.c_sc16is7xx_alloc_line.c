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
 int BITS_PER_LONG ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int SC16IS7XX_MAX_DEVS ; 
 int /*<<< orphan*/  sc16is7xx_lines ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sc16is7xx_alloc_line(void)
{
	int i;

	BUILD_BUG_ON(SC16IS7XX_MAX_DEVS > BITS_PER_LONG);

	for (i = 0; i < SC16IS7XX_MAX_DEVS; i++)
		if (!test_and_set_bit(i, &sc16is7xx_lines))
			break;

	return i;
}