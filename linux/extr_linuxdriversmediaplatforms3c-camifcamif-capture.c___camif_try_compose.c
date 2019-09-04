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
struct v4l2_rect {int dummy; } ;
struct TYPE_4__ {struct v4l2_rect rect; } ;
struct camif_vp {TYPE_2__ out_frame; } ;
struct camif_dev {TYPE_1__* variant; } ;
struct TYPE_3__ {scalar_t__ ip_revision; } ;

/* Variables and functions */
 scalar_t__ S3C244X_CAMIF_IP_REV ; 

__attribute__((used)) static void __camif_try_compose(struct camif_dev *camif, struct camif_vp *vp,
				struct v4l2_rect *r)
{
	/* s3c244x doesn't support composition */
	if (camif->variant->ip_revision == S3C244X_CAMIF_IP_REV) {
		*r = vp->out_frame.rect;
		return;
	}

	/* TODO: s3c64xx */
}