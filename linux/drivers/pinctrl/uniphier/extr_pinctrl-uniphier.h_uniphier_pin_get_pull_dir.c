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
 unsigned long UNIPHIER_PIN_PULL_DIR_MASK ; 
 unsigned long UNIPHIER_PIN_PULL_DIR_SHIFT ; 

__attribute__((used)) static inline unsigned int uniphier_pin_get_pull_dir(void *drv_data)
{
	return ((unsigned long)drv_data >> UNIPHIER_PIN_PULL_DIR_SHIFT) &
						UNIPHIER_PIN_PULL_DIR_MASK;
}