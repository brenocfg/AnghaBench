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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_IP_TYPE_VIPA ; 
 int /*<<< orphan*/  QETH_PROT_IPV4 ; 
 int /*<<< orphan*/  qeth_l3_dev_ip_add_show (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t qeth_l3_dev_vipa_add4_show(struct device *dev,
					  struct device_attribute *attr,
					  char *buf)
{
	return qeth_l3_dev_ip_add_show(dev, buf, QETH_PROT_IPV4,
				       QETH_IP_TYPE_VIPA);
}