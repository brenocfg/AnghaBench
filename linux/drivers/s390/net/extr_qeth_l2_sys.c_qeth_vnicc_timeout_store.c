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
typedef  int /*<<< orphan*/  u32 ;
struct qeth_card {int /*<<< orphan*/  conf_mutex; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 int kstrtou32 (char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int qeth_l2_vnicc_set_timeout (struct qeth_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t qeth_vnicc_timeout_store(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t count)
{
	struct qeth_card *card = dev_get_drvdata(dev);
	u32 timeout;
	int rc;

	if (!card)
		return -EINVAL;

	rc = kstrtou32(buf, 10, &timeout);
	if (rc)
		return rc;

	mutex_lock(&card->conf_mutex);
	rc = qeth_l2_vnicc_set_timeout(card, timeout);
	mutex_unlock(&card->conf_mutex);
	return rc ? rc : count;
}