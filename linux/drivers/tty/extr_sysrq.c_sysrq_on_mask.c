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
 scalar_t__ sysrq_always_enabled ; 
 int sysrq_enabled ; 

__attribute__((used)) static bool sysrq_on_mask(int mask)
{
	return sysrq_always_enabled ||
	       sysrq_enabled == 1 ||
	       (sysrq_enabled & mask);
}