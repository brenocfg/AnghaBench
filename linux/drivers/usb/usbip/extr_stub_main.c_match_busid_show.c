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
struct device_driver {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {char* name; int /*<<< orphan*/  busid_lock; } ;

/* Variables and functions */
 int MAX_BUSID ; 
 TYPE_1__* busid_table ; 
 int /*<<< orphan*/  busid_table_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t match_busid_show(struct device_driver *drv, char *buf)
{
	int i;
	char *out = buf;

	spin_lock(&busid_table_lock);
	for (i = 0; i < MAX_BUSID; i++) {
		spin_lock(&busid_table[i].busid_lock);
		if (busid_table[i].name[0])
			out += sprintf(out, "%s ", busid_table[i].name);
		spin_unlock(&busid_table[i].busid_lock);
	}
	spin_unlock(&busid_table_lock);
	out += sprintf(out, "\n");

	return out - buf;
}