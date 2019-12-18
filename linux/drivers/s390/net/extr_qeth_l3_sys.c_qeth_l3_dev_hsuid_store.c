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
struct TYPE_4__ {scalar_t__ cq; char* hsuid; scalar_t__ sniffer; } ;
struct qeth_card {scalar_t__ state; TYPE_2__ options; TYPE_1__* dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  perm_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASCEBC (char*,int) ; 
 scalar_t__ CARD_STATE_DOWN ; 
 size_t EINVAL ; 
 size_t EPERM ; 
 int /*<<< orphan*/  IS_IQD (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_CQ_DISABLED ; 
 int /*<<< orphan*/  QETH_CQ_ENABLED ; 
 scalar_t__ QETH_CQ_NOTAVAILABLE ; 
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ qeth_configure_cq (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int qeth_l3_modify_hsuid (struct qeth_card*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int strlen (char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static ssize_t qeth_l3_dev_hsuid_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct qeth_card *card = dev_get_drvdata(dev);
	char *tmp;
	int rc;

	if (!card)
		return -EINVAL;

	if (!IS_IQD(card))
		return -EPERM;
	if (card->state != CARD_STATE_DOWN)
		return -EPERM;
	if (card->options.sniffer)
		return -EPERM;
	if (card->options.cq == QETH_CQ_NOTAVAILABLE)
		return -EPERM;

	tmp = strsep((char **)&buf, "\n");
	if (strlen(tmp) > 8)
		return -EINVAL;

	if (card->options.hsuid[0])
		/* delete old ip address */
		qeth_l3_modify_hsuid(card, false);

	if (strlen(tmp) == 0) {
		/* delete ip address only */
		card->options.hsuid[0] = '\0';
		memcpy(card->dev->perm_addr, card->options.hsuid, 9);
		qeth_configure_cq(card, QETH_CQ_DISABLED);
		return count;
	}

	if (qeth_configure_cq(card, QETH_CQ_ENABLED))
		return -EPERM;

	snprintf(card->options.hsuid, sizeof(card->options.hsuid),
		 "%-8s", tmp);
	ASCEBC(card->options.hsuid, 8);
	memcpy(card->dev->perm_addr, card->options.hsuid, 9);

	rc = qeth_l3_modify_hsuid(card, true);

	return rc ? rc : count;
}