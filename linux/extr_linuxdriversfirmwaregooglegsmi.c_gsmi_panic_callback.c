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
 int /*<<< orphan*/  GSMI_SHUTDOWN_PANIC ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  gsmi_shutdown_reason (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gsmi_panic_callback(struct notifier_block *nb,
			       unsigned long reason, void *arg)
{
	gsmi_shutdown_reason(GSMI_SHUTDOWN_PANIC);
	return NOTIFY_DONE;
}