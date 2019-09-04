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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct dummy {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_attr_looptest ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct dummy*) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dummy*) ; 
 struct dummy* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pl022_dummy_probe(struct spi_device *spi)
{
	struct dummy *p_dummy;
	int status;

	dev_info(&spi->dev, "probing dummy SPI device\n");

	p_dummy = kzalloc(sizeof *p_dummy, GFP_KERNEL);
	if (!p_dummy)
		return -ENOMEM;

	dev_set_drvdata(&spi->dev, p_dummy);
	mutex_init(&p_dummy->lock);

	/* sysfs hook */
	status = device_create_file(&spi->dev, &dev_attr_looptest);
	if (status) {
		dev_dbg(&spi->dev, "device_create_file looptest failure.\n");
		goto out_dev_create_looptest_failed;
	}

	return 0;

out_dev_create_looptest_failed:
	dev_set_drvdata(&spi->dev, NULL);
	kfree(p_dummy);
	return status;
}