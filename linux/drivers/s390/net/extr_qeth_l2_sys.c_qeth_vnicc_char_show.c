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
typedef  int /*<<< orphan*/  u32 ;
struct qeth_card {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 int qeth_l2_vnicc_get_state (struct qeth_card*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  qeth_l2_vnicc_sysfs_attr_to_char (int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t qeth_vnicc_char_show(struct device *dev,
				    struct device_attribute *attr, char *buf)
{
	struct qeth_card *card = dev_get_drvdata(dev);
	bool state;
	u32 vnicc;
	int rc;

	if (!card)
		return -EINVAL;

	vnicc = qeth_l2_vnicc_sysfs_attr_to_char(attr->attr.name);
	rc = qeth_l2_vnicc_get_state(card, vnicc, &state);

	if (rc == -EBUSY)
		return sprintf(buf, "n/a (BridgePort)\n");
	if (rc == -EOPNOTSUPP)
		return sprintf(buf, "n/a\n");
	return rc ? rc : sprintf(buf, "%d\n", state);
}