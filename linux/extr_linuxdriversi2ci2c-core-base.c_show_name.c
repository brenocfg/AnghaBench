#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/ * type; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {char* name; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_client_type ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 TYPE_2__* to_i2c_adapter (struct device*) ; 
 TYPE_1__* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t
show_name(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%s\n", dev->type == &i2c_client_type ?
		       to_i2c_client(dev)->name : to_i2c_adapter(dev)->name);
}