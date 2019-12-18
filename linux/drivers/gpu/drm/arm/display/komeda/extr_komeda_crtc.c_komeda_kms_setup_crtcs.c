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
struct komeda_pipeline {int /*<<< orphan*/  id; } ;
struct komeda_kms_dev {size_t n_crtcs; struct komeda_crtc* crtcs; } ;
struct komeda_dev {int n_pipelines; struct komeda_pipeline** pipelines; } ;
struct komeda_crtc {TYPE_1__* slave; struct komeda_pipeline* master; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,size_t,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* komeda_pipeline_get_slave (struct komeda_pipeline*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

int komeda_kms_setup_crtcs(struct komeda_kms_dev *kms,
			   struct komeda_dev *mdev)
{
	struct komeda_crtc *crtc;
	struct komeda_pipeline *master;
	char str[16];
	int i;

	kms->n_crtcs = 0;

	for (i = 0; i < mdev->n_pipelines; i++) {
		crtc = &kms->crtcs[kms->n_crtcs];
		master = mdev->pipelines[i];

		crtc->master = master;
		crtc->slave  = komeda_pipeline_get_slave(master);

		if (crtc->slave)
			sprintf(str, "pipe-%d", crtc->slave->id);
		else
			sprintf(str, "None");

		DRM_INFO("CRTC-%d: master(pipe-%d) slave(%s).\n",
			 kms->n_crtcs, master->id, str);

		kms->n_crtcs++;
	}

	return 0;
}