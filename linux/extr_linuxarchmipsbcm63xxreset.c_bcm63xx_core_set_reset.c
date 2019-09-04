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
typedef  enum bcm63xx_core_reset { ____Placeholder_bcm63xx_core_reset } bcm63xx_core_reset ;

/* Variables and functions */
 int /*<<< orphan*/  __bcm63xx_core_set_reset (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * bcm63xx_reset_bits ; 

void bcm63xx_core_set_reset(enum bcm63xx_core_reset core, int reset)
{
	__bcm63xx_core_set_reset(bcm63xx_reset_bits[core], reset);
}