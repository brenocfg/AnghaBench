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
struct TYPE_2__ {unsigned int msi_index; } ;
struct msi_desc {int /*<<< orphan*/  list; TYPE_1__ fsl_mc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct msi_desc* alloc_msi_entry (struct device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_to_msi_list (struct device*) ; 
 int /*<<< orphan*/  fsl_mc_msi_free_descs (struct device*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsl_mc_msi_alloc_descs(struct device *dev, unsigned int irq_count)

{
	unsigned int i;
	int error;
	struct msi_desc *msi_desc;

	for (i = 0; i < irq_count; i++) {
		msi_desc = alloc_msi_entry(dev, 1, NULL);
		if (!msi_desc) {
			dev_err(dev, "Failed to allocate msi entry\n");
			error = -ENOMEM;
			goto cleanup_msi_descs;
		}

		msi_desc->fsl_mc.msi_index = i;
		INIT_LIST_HEAD(&msi_desc->list);
		list_add_tail(&msi_desc->list, dev_to_msi_list(dev));
	}

	return 0;

cleanup_msi_descs:
	fsl_mc_msi_free_descs(dev);
	return error;
}