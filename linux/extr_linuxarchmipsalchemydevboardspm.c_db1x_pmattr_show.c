#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct TYPE_2__ {int* name; } ;
struct kobj_attribute {TYPE_1__ attr; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ ATTRCMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOENT ; 
 int SYS_WAKEMSK_GPIO (int) ; 
 int SYS_WAKEMSK_M2 ; 
 int db1x_pm_last_wakesrc ; 
 int db1x_pm_sleep_secs ; 
 int db1x_pm_wakemsk ; 
 int /*<<< orphan*/  gpio0 ; 
 int /*<<< orphan*/  gpio1 ; 
 int /*<<< orphan*/  gpio2 ; 
 int /*<<< orphan*/  gpio3 ; 
 int /*<<< orphan*/  gpio4 ; 
 int /*<<< orphan*/  gpio5 ; 
 int /*<<< orphan*/  gpio6 ; 
 int /*<<< orphan*/  gpio7 ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  timer_timeout ; 
 int /*<<< orphan*/  wakemsk ; 
 int /*<<< orphan*/  wakesrc ; 

__attribute__((used)) static ssize_t db1x_pmattr_show(struct kobject *kobj,
				struct kobj_attribute *attr,
				char *buf)
{
	int idx;

	if (ATTRCMP(timer_timeout))
		return sprintf(buf, "%lu\n", db1x_pm_sleep_secs);

	else if (ATTRCMP(timer))
		return sprintf(buf, "%u\n",
				!!(db1x_pm_wakemsk & SYS_WAKEMSK_M2));

	else if (ATTRCMP(wakesrc))
		return sprintf(buf, "%lu\n", db1x_pm_last_wakesrc);

	else if (ATTRCMP(gpio0) || ATTRCMP(gpio1) || ATTRCMP(gpio2) ||
		 ATTRCMP(gpio3) || ATTRCMP(gpio4) || ATTRCMP(gpio5) ||
		 ATTRCMP(gpio6) || ATTRCMP(gpio7)) {
		idx = (attr->attr.name)[4] - '0';
		return sprintf(buf, "%d\n",
			!!(db1x_pm_wakemsk & SYS_WAKEMSK_GPIO(idx)));

	} else if (ATTRCMP(wakemsk)) {
		return sprintf(buf, "%08lx\n", db1x_pm_wakemsk);
	}

	return -ENOENT;
}