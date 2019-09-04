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
struct tpm_chip {int /*<<< orphan*/  dev; } ;
struct proxy_dev {struct tpm_chip* chip; int /*<<< orphan*/  work; int /*<<< orphan*/  buf_lock; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct proxy_dev* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct tpm_chip*) ; 
 int PTR_ERR (struct tpm_chip*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct proxy_dev*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct proxy_dev*) ; 
 struct proxy_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct tpm_chip* tpm_chip_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtpm_proxy_tpm_ops ; 
 int /*<<< orphan*/  vtpm_proxy_work ; 

__attribute__((used)) static struct proxy_dev *vtpm_proxy_create_proxy_dev(void)
{
	struct proxy_dev *proxy_dev;
	struct tpm_chip *chip;
	int err;

	proxy_dev = kzalloc(sizeof(*proxy_dev), GFP_KERNEL);
	if (proxy_dev == NULL)
		return ERR_PTR(-ENOMEM);

	init_waitqueue_head(&proxy_dev->wq);
	mutex_init(&proxy_dev->buf_lock);
	INIT_WORK(&proxy_dev->work, vtpm_proxy_work);

	chip = tpm_chip_alloc(NULL, &vtpm_proxy_tpm_ops);
	if (IS_ERR(chip)) {
		err = PTR_ERR(chip);
		goto err_proxy_dev_free;
	}
	dev_set_drvdata(&chip->dev, proxy_dev);

	proxy_dev->chip = chip;

	return proxy_dev;

err_proxy_dev_free:
	kfree(proxy_dev);

	return ERR_PTR(err);
}