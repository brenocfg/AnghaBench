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
 scalar_t__ SYSTEM_RUNNING ; 
 scalar_t__ irqs_disabled () ; 
 scalar_t__ system_state ; 

__attribute__((used)) static inline bool i2c_in_atomic_xfer_mode(void)
{
	return system_state > SYSTEM_RUNNING && irqs_disabled();
}