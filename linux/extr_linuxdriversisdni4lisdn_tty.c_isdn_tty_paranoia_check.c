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
typedef  int /*<<< orphan*/  modem_info ;

/* Variables and functions */

__attribute__((used)) static inline int
isdn_tty_paranoia_check(modem_info *info, char *name, const char *routine)
{
#ifdef MODEM_PARANOIA_CHECK
	if (!info) {
		printk(KERN_WARNING "isdn_tty: null info_struct for %s in %s\n",
		       name, routine);
		return 1;
	}
	if (info->magic != ISDN_ASYNC_MAGIC) {
		printk(KERN_WARNING "isdn_tty: bad magic for modem struct %s in %s\n",
		       name, routine);
		return 1;
	}
#endif
	return 0;
}