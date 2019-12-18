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
struct gb_svc {int ap_intf_id; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct gb_svc* to_gb_svc (struct device*) ; 

__attribute__((used)) static ssize_t ap_intf_id_show(struct device *dev,
			       struct device_attribute *attr, char *buf)
{
	struct gb_svc *svc = to_gb_svc(dev);

	return sprintf(buf, "%u\n", svc->ap_intf_id);
}