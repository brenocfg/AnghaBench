#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct camif_vp {TYPE_2__* camif; } ;
struct TYPE_4__ {TYPE_1__* variant; } ;
struct TYPE_3__ {unsigned int ip_revision; } ;

/* Variables and functions */
 unsigned int S3C244X_CAMIF_IP_REV ; 
 int /*<<< orphan*/  camif_s3c244x_hw_set_scaler (struct camif_vp*) ; 
 int /*<<< orphan*/  camif_s3c64xx_hw_set_scaler (struct camif_vp*) ; 

void camif_hw_set_scaler(struct camif_vp *vp)
{
	unsigned int ip_rev = vp->camif->variant->ip_revision;

	if (ip_rev == S3C244X_CAMIF_IP_REV)
		camif_s3c244x_hw_set_scaler(vp);
	else
		camif_s3c64xx_hw_set_scaler(vp);
}