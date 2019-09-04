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
 int /*<<< orphan*/  cb_restart () ; 
 scalar_t__ reg_restart ; 
 scalar_t__ rst_base ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int rockchip_restart_notify(struct notifier_block *this,
				   unsigned long mode, void *cmd)
{
	if (cb_restart)
		cb_restart();

	writel(0xfdb9, rst_base + reg_restart);
	return NOTIFY_DONE;
}