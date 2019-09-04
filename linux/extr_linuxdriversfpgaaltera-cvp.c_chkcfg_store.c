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
struct device_driver {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  altera_cvp_chkcfg ; 
 int kstrtobool (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t chkcfg_store(struct device_driver *drv, const char *buf,
			    size_t count)
{
	int ret;

	ret = kstrtobool(buf, &altera_cvp_chkcfg);
	if (ret)
		return ret;

	return count;
}