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
struct TYPE_5__ {int /*<<< orphan*/  mtu; int /*<<< orphan*/  mac; int /*<<< orphan*/  name; int /*<<< orphan*/ * queue_count; int /*<<< orphan*/  features; } ;
struct TYPE_6__ {TYPE_2__ config; int /*<<< orphan*/  max_mcast_filters; int /*<<< orphan*/  max_ucast_filters; } ;
union ionic_lif_identity {TYPE_3__ eth; int /*<<< orphan*/  capabilities; } ;
typedef  int /*<<< orphan*/  u8 ;
struct ionic_dev {TYPE_1__* dev_cmd_regs; } ;
struct ionic {int /*<<< orphan*/  dev; int /*<<< orphan*/  dev_cmd_lock; struct ionic_dev idev; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVCMD_TIMEOUT ; 
 int /*<<< orphan*/  IONIC_IDENTITY_VERSION_1 ; 
 size_t IONIC_QTYPE_ADMINQ ; 
 size_t IONIC_QTYPE_NOTIFYQ ; 
 size_t IONIC_QTYPE_RXQ ; 
 size_t IONIC_QTYPE_TXQ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ionic_dev_cmd_lif_identify (struct ionic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ionic_dev_cmd_wait (struct ionic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_fromio (union ionic_lif_identity*,int /*<<< orphan*/ *,size_t) ; 
 size_t min (int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ionic_lif_identify(struct ionic *ionic, u8 lif_type,
		       union ionic_lif_identity *lid)
{
	struct ionic_dev *idev = &ionic->idev;
	size_t sz;
	int err;

	sz = min(sizeof(*lid), sizeof(idev->dev_cmd_regs->data));

	mutex_lock(&ionic->dev_cmd_lock);
	ionic_dev_cmd_lif_identify(idev, lif_type, IONIC_IDENTITY_VERSION_1);
	err = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
	memcpy_fromio(lid, &idev->dev_cmd_regs->data, sz);
	mutex_unlock(&ionic->dev_cmd_lock);
	if (err)
		return (err);

	dev_dbg(ionic->dev, "capabilities 0x%llx\n",
		le64_to_cpu(lid->capabilities));

	dev_dbg(ionic->dev, "eth.max_ucast_filters %d\n",
		le32_to_cpu(lid->eth.max_ucast_filters));
	dev_dbg(ionic->dev, "eth.max_mcast_filters %d\n",
		le32_to_cpu(lid->eth.max_mcast_filters));
	dev_dbg(ionic->dev, "eth.features 0x%llx\n",
		le64_to_cpu(lid->eth.config.features));
	dev_dbg(ionic->dev, "eth.queue_count[IONIC_QTYPE_ADMINQ] %d\n",
		le32_to_cpu(lid->eth.config.queue_count[IONIC_QTYPE_ADMINQ]));
	dev_dbg(ionic->dev, "eth.queue_count[IONIC_QTYPE_NOTIFYQ] %d\n",
		le32_to_cpu(lid->eth.config.queue_count[IONIC_QTYPE_NOTIFYQ]));
	dev_dbg(ionic->dev, "eth.queue_count[IONIC_QTYPE_RXQ] %d\n",
		le32_to_cpu(lid->eth.config.queue_count[IONIC_QTYPE_RXQ]));
	dev_dbg(ionic->dev, "eth.queue_count[IONIC_QTYPE_TXQ] %d\n",
		le32_to_cpu(lid->eth.config.queue_count[IONIC_QTYPE_TXQ]));
	dev_dbg(ionic->dev, "eth.config.name %s\n", lid->eth.config.name);
	dev_dbg(ionic->dev, "eth.config.mac %pM\n", lid->eth.config.mac);
	dev_dbg(ionic->dev, "eth.config.mtu %d\n",
		le32_to_cpu(lid->eth.config.mtu));

	return 0;
}