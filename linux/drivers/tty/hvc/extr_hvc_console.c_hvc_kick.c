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
 int hvc_kicked ; 
 int /*<<< orphan*/  hvc_task ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

void hvc_kick(void)
{
	hvc_kicked = 1;
	wake_up_process(hvc_task);
}