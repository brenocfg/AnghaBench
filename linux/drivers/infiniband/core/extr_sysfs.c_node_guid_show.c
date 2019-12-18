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
struct ib_device {int /*<<< orphan*/  node_guid; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct ib_device* rdma_device_to_ibdev (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int) ; 

__attribute__((used)) static ssize_t node_guid_show(struct device *device,
			      struct device_attribute *attr, char *buf)
{
	struct ib_device *dev = rdma_device_to_ibdev(device);

	return sprintf(buf, "%04x:%04x:%04x:%04x\n",
		       be16_to_cpu(((__be16 *) &dev->node_guid)[0]),
		       be16_to_cpu(((__be16 *) &dev->node_guid)[1]),
		       be16_to_cpu(((__be16 *) &dev->node_guid)[2]),
		       be16_to_cpu(((__be16 *) &dev->node_guid)[3]));
}