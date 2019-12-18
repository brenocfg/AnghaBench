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
typedef  int u8 ;
struct TYPE_4__ {int /*<<< orphan*/  conf; } ;
struct dp_altmode {int /*<<< orphan*/  lock; TYPE_2__ data; TYPE_1__* alt; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  vdo; } ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 int DP_CAP_CAPABILITY (int /*<<< orphan*/ ) ; 
 int DP_CAP_DFP_D ; 
 int DP_CAP_UFP_D ; 
 int DP_CONF_CURRENTLY (int /*<<< orphan*/ ) ; 
 int DP_CONF_DFP_D ; 
 int DP_CONF_UFP_D ; 
 char** configurations ; 
 struct dp_altmode* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t configuration_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	struct dp_altmode *dp = dev_get_drvdata(dev);
	int len;
	u8 cap;
	u8 cur;
	int i;

	mutex_lock(&dp->lock);

	cap = DP_CAP_CAPABILITY(dp->alt->vdo);
	cur = DP_CONF_CURRENTLY(dp->data.conf);

	len = sprintf(buf, "%s ", cur ? "USB" : "[USB]");

	for (i = 1; i < ARRAY_SIZE(configurations); i++) {
		if (i == cur)
			len += sprintf(buf + len, "[%s] ", configurations[i]);
		else if ((i == DP_CONF_DFP_D && cap & DP_CAP_DFP_D) ||
			 (i == DP_CONF_UFP_D && cap & DP_CAP_UFP_D))
			len += sprintf(buf + len, "%s ", configurations[i]);
	}

	mutex_unlock(&dp->lock);

	buf[len - 1] = '\n';
	return len;
}