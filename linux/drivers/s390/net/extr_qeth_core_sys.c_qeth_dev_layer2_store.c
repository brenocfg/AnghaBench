#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ layer_enforced; } ;
struct TYPE_4__ {int layer; } ;
struct qeth_card {scalar_t__ state; int /*<<< orphan*/  discipline_mutex; int /*<<< orphan*/  gdev; TYPE_3__* discipline; struct net_device* dev; TYPE_2__ info; TYPE_1__ options; } ;
struct net_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  enum qeth_discipline_id { ____Placeholder_qeth_discipline_id } qeth_discipline_id ;
struct TYPE_6__ {int (* setup ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* remove ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ CARD_STATE_DOWN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int QETH_DISCIPLINE_LAYER2 ; 
 int QETH_DISCIPLINE_LAYER3 ; 
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct net_device* qeth_clone_netdev (struct net_device*) ; 
 int /*<<< orphan*/  qeth_core_free_discipline (struct qeth_card*) ; 
 int qeth_core_load_discipline (struct qeth_card*,int) ; 
 int simple_strtoul (char const*,char**,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t qeth_dev_layer2_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct qeth_card *card = dev_get_drvdata(dev);
	struct net_device *ndev;
	char *tmp;
	int i, rc = 0;
	enum qeth_discipline_id newdis;

	if (!card)
		return -EINVAL;

	mutex_lock(&card->discipline_mutex);
	if (card->state != CARD_STATE_DOWN) {
		rc = -EPERM;
		goto out;
	}

	i = simple_strtoul(buf, &tmp, 16);
	switch (i) {
	case 0:
		newdis = QETH_DISCIPLINE_LAYER3;
		break;
	case 1:
		newdis = QETH_DISCIPLINE_LAYER2;
		break;
	default:
		rc = -EINVAL;
		goto out;
	}

	if (card->options.layer == newdis)
		goto out;
	if (card->info.layer_enforced) {
		/* fixed layer, can't switch */
		rc = -EOPNOTSUPP;
		goto out;
	}

	if (card->discipline) {
		/* start with a new, pristine netdevice: */
		ndev = qeth_clone_netdev(card->dev);
		if (!ndev) {
			rc = -ENOMEM;
			goto out;
		}

		card->discipline->remove(card->gdev);
		qeth_core_free_discipline(card);
		free_netdev(card->dev);
		card->dev = ndev;
	}

	rc = qeth_core_load_discipline(card, newdis);
	if (rc)
		goto out;

	rc = card->discipline->setup(card->gdev);
	if (rc)
		qeth_core_free_discipline(card);
out:
	mutex_unlock(&card->discipline_mutex);
	return rc ? rc : count;
}