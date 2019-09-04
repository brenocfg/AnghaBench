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
struct poll_table_struct {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */

__attribute__((used)) static __poll_t hostaudio_poll(struct file *file,
				struct poll_table_struct *wait)
{
	__poll_t mask = 0;

#ifdef DEBUG
	printk(KERN_DEBUG "hostaudio: poll called (unimplemented)\n");
#endif

	return mask;
}