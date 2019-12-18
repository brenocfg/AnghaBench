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
struct file {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  pnx833x_wdt_ping () ; 

__attribute__((used)) static ssize_t pnx833x_wdt_write(struct file *file, const char *data, size_t len, loff_t *ppos)
{
	/* Refresh the timer. */
	if (len)
		pnx833x_wdt_ping();

	return len;
}