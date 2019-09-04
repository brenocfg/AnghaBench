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
struct device_node {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {struct device_node* of_node; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,struct device_node*) ; 

__attribute__((used)) static ssize_t devspec_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct device_node *of_node = dev->of_node;

	return sprintf(buf, "%pOF\n", of_node);
}