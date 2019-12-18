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
struct komeda_kms_dev {int n_crtcs; int /*<<< orphan*/ * crtcs; } ;
struct komeda_dev {int dummy; } ;

/* Variables and functions */
 int komeda_wb_connector_add (struct komeda_kms_dev*,int /*<<< orphan*/ *) ; 

int komeda_kms_add_wb_connectors(struct komeda_kms_dev *kms,
				 struct komeda_dev *mdev)
{
	int i, err;

	for (i = 0; i < kms->n_crtcs; i++) {
		err = komeda_wb_connector_add(kms, &kms->crtcs[i]);
		if (err)
			return err;
	}

	return 0;
}