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
struct ceu_device {scalar_t__ num_sd; scalar_t__ sd_index; int /*<<< orphan*/ * sd; void* asds; int /*<<< orphan*/  dev; void* subdevs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* devm_kcalloc (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ceu_init_async_subdevs(struct ceu_device *ceudev, unsigned int n_sd)
{
	/* Reserve memory for 'n_sd' ceu_subdev descriptors. */
	ceudev->subdevs = devm_kcalloc(ceudev->dev, n_sd,
				       sizeof(*ceudev->subdevs), GFP_KERNEL);
	if (!ceudev->subdevs)
		return -ENOMEM;

	/*
	 * Reserve memory for 'n_sd' pointers to async_subdevices.
	 * ceudev->asds members will point to &ceu_subdev.asd
	 */
	ceudev->asds = devm_kcalloc(ceudev->dev, n_sd,
				    sizeof(*ceudev->asds), GFP_KERNEL);
	if (!ceudev->asds)
		return -ENOMEM;

	ceudev->sd = NULL;
	ceudev->sd_index = 0;
	ceudev->num_sd = 0;

	return 0;
}