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
 int NOTIFY_DONE ; 
 scalar_t__ base ; 
 int /*<<< orphan*/  cpu_do_idle () ; 
 scalar_t__ reboot_offset ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int hisi_restart_handler(struct notifier_block *this,
				unsigned long mode, void *cmd)
{
	writel_relaxed(0xdeadbeef, base + reboot_offset);

	while (1)
		cpu_do_idle();

	return NOTIFY_DONE;
}