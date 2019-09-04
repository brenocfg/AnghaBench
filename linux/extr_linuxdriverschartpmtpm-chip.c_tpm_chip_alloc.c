#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct tpm_class_ops {int dummy; } ;
struct TYPE_11__ {void* devt; int /*<<< orphan*/  release; TYPE_2__* class; struct device* parent; int /*<<< orphan*/  groups; } ;
struct TYPE_9__ {void* session_buf; void* context_buf; } ;
struct TYPE_12__ {void* owner; } ;
struct tpm_chip {int dev_num; int flags; int locality; TYPE_4__ dev; TYPE_4__ devs; TYPE_1__ work_space; TYPE_8__ cdevs; TYPE_8__ cdev; int /*<<< orphan*/  groups; struct tpm_class_ops const* ops; int /*<<< orphan*/  ops_sem; int /*<<< orphan*/  tpm_mutex; } ;
struct device {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  shutdown_pre; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct tpm_chip* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MISC_MAJOR ; 
 void* MKDEV (int /*<<< orphan*/ ,int) ; 
 int PAGE_SIZE ; 
 void* THIS_MODULE ; 
 int TPM_CHIP_FLAG_TPM2 ; 
 int TPM_CHIP_FLAG_VIRTUAL ; 
 int TPM_MINOR ; 
 int TPM_NUM_DEVICES ; 
 int /*<<< orphan*/  cdev_init (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_nums_idr ; 
 int dev_set_name (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  device_initialize (TYPE_4__*) ; 
 int /*<<< orphan*/  get_device (TYPE_4__*) ; 
 int idr_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_lock ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tpm_chip*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_4__*) ; 
 TYPE_2__* tpm_class ; 
 int /*<<< orphan*/  tpm_class_shutdown ; 
 int /*<<< orphan*/  tpm_dev_release ; 
 int /*<<< orphan*/  tpm_devs_release ; 
 int /*<<< orphan*/  tpm_devt ; 
 int /*<<< orphan*/  tpm_fops ; 
 TYPE_2__* tpmrm_class ; 
 int /*<<< orphan*/  tpmrm_fops ; 

struct tpm_chip *tpm_chip_alloc(struct device *pdev,
				const struct tpm_class_ops *ops)
{
	struct tpm_chip *chip;
	int rc;

	chip = kzalloc(sizeof(*chip), GFP_KERNEL);
	if (chip == NULL)
		return ERR_PTR(-ENOMEM);

	mutex_init(&chip->tpm_mutex);
	init_rwsem(&chip->ops_sem);

	chip->ops = ops;

	mutex_lock(&idr_lock);
	rc = idr_alloc(&dev_nums_idr, NULL, 0, TPM_NUM_DEVICES, GFP_KERNEL);
	mutex_unlock(&idr_lock);
	if (rc < 0) {
		dev_err(pdev, "No available tpm device numbers\n");
		kfree(chip);
		return ERR_PTR(rc);
	}
	chip->dev_num = rc;

	device_initialize(&chip->dev);
	device_initialize(&chip->devs);

	chip->dev.class = tpm_class;
	chip->dev.class->shutdown_pre = tpm_class_shutdown;
	chip->dev.release = tpm_dev_release;
	chip->dev.parent = pdev;
	chip->dev.groups = chip->groups;

	chip->devs.parent = pdev;
	chip->devs.class = tpmrm_class;
	chip->devs.release = tpm_devs_release;
	/* get extra reference on main device to hold on
	 * behalf of devs.  This holds the chip structure
	 * while cdevs is in use.  The corresponding put
	 * is in the tpm_devs_release (TPM2 only)
	 */
	if (chip->flags & TPM_CHIP_FLAG_TPM2)
		get_device(&chip->dev);

	if (chip->dev_num == 0)
		chip->dev.devt = MKDEV(MISC_MAJOR, TPM_MINOR);
	else
		chip->dev.devt = MKDEV(MAJOR(tpm_devt), chip->dev_num);

	chip->devs.devt =
		MKDEV(MAJOR(tpm_devt), chip->dev_num + TPM_NUM_DEVICES);

	rc = dev_set_name(&chip->dev, "tpm%d", chip->dev_num);
	if (rc)
		goto out;
	rc = dev_set_name(&chip->devs, "tpmrm%d", chip->dev_num);
	if (rc)
		goto out;

	if (!pdev)
		chip->flags |= TPM_CHIP_FLAG_VIRTUAL;

	cdev_init(&chip->cdev, &tpm_fops);
	cdev_init(&chip->cdevs, &tpmrm_fops);
	chip->cdev.owner = THIS_MODULE;
	chip->cdevs.owner = THIS_MODULE;

	chip->work_space.context_buf = kzalloc(PAGE_SIZE, GFP_KERNEL);
	if (!chip->work_space.context_buf) {
		rc = -ENOMEM;
		goto out;
	}
	chip->work_space.session_buf = kzalloc(PAGE_SIZE, GFP_KERNEL);
	if (!chip->work_space.session_buf) {
		rc = -ENOMEM;
		goto out;
	}

	chip->locality = -1;
	return chip;

out:
	put_device(&chip->devs);
	put_device(&chip->dev);
	return ERR_PTR(rc);
}