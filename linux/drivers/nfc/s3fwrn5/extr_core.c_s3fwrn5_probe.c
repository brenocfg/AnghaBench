#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct s3fwrn5_phy_ops {int dummy; } ;
struct TYPE_4__ {struct nci_dev* ndev; } ;
struct s3fwrn5_info {unsigned int max_payload; struct nci_dev* ndev; TYPE_1__ fw_info; int /*<<< orphan*/  mutex; struct s3fwrn5_phy_ops const* phy_ops; struct device* pdev; void* phy_id; } ;
struct nci_dev {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  n_prop_ops; int /*<<< orphan*/  prop_ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  S3FWRN5_MODE_COLD ; 
 int /*<<< orphan*/  S3FWRN5_NFC_PROTOCOLS ; 
 struct s3fwrn5_info* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct nci_dev* nci_allocate_device (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_free_device (struct nci_dev*) ; 
 int nci_register_device (struct nci_dev*) ; 
 int /*<<< orphan*/  nci_set_drvdata (struct nci_dev*,struct s3fwrn5_info*) ; 
 int /*<<< orphan*/  nci_set_parent_dev (struct nci_dev*,struct device*) ; 
 int /*<<< orphan*/  s3fwrn5_nci_get_prop_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__ s3fwrn5_nci_ops ; 
 int /*<<< orphan*/  s3fwrn5_set_mode (struct s3fwrn5_info*,int /*<<< orphan*/ ) ; 

int s3fwrn5_probe(struct nci_dev **ndev, void *phy_id, struct device *pdev,
	const struct s3fwrn5_phy_ops *phy_ops, unsigned int max_payload)
{
	struct s3fwrn5_info *info;
	int ret;

	info = devm_kzalloc(pdev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->phy_id = phy_id;
	info->pdev = pdev;
	info->phy_ops = phy_ops;
	info->max_payload = max_payload;
	mutex_init(&info->mutex);

	s3fwrn5_set_mode(info, S3FWRN5_MODE_COLD);

	s3fwrn5_nci_get_prop_ops(&s3fwrn5_nci_ops.prop_ops,
		&s3fwrn5_nci_ops.n_prop_ops);

	info->ndev = nci_allocate_device(&s3fwrn5_nci_ops,
		S3FWRN5_NFC_PROTOCOLS, 0, 0);
	if (!info->ndev)
		return -ENOMEM;

	nci_set_parent_dev(info->ndev, pdev);
	nci_set_drvdata(info->ndev, info);

	ret = nci_register_device(info->ndev);
	if (ret < 0) {
		nci_free_device(info->ndev);
		return ret;
	}

	info->fw_info.ndev = info->ndev;

	*ndev = info->ndev;

	return ret;
}