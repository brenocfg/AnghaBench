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
struct iscsi_endpoint {scalar_t__ id; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct iscsi_endpoint* iscsi_dev_to_endpoint (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long) ; 

__attribute__((used)) static ssize_t
show_ep_handle(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct iscsi_endpoint *ep = iscsi_dev_to_endpoint(dev);
	return sprintf(buf, "%llu\n", (unsigned long long) ep->id);
}