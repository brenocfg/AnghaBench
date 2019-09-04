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
 scalar_t__ SWRST ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 scalar_t__ reg_base ; 

__attribute__((used)) static int s3c2443_restart(struct notifier_block *this,
			   unsigned long mode, void *cmd)
{
	__raw_writel(0x533c2443, reg_base + SWRST);
	return NOTIFY_DONE;
}