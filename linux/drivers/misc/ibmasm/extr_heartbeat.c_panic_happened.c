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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int suspend_heartbeats ; 

__attribute__((used)) static int panic_happened(struct notifier_block *n, unsigned long val, void *v)
{
	suspend_heartbeats = 1;
	return 0;
}