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
struct controller_priv {int design_no; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct controller_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t design_number_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	struct controller_priv *cd = dev_get_drvdata(dev);

	return sprintf(buf, "%d\n", cd->design_no);
}