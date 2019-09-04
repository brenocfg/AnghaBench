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
typedef  int u8 ;

/* Variables and functions */
 int VIPER_VERSION ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static u8 viper_hw_version(void)
{
	u8 v1, v2;
	unsigned long flags;

	local_irq_save(flags);

	VIPER_VERSION = 0;
	v1 = VIPER_VERSION;
	VIPER_VERSION = 0xff;
	v2 = VIPER_VERSION;

	v1 = (v1 != v2 || v1 == 0xff) ? 0 : v1;

	local_irq_restore(flags);
	return v1;
}