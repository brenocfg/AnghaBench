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
typedef  int /*<<< orphan*/  u32 ;
struct komeda_pipeline {int dummy; } ;
struct komeda_kms_dev {int n_crtcs; struct komeda_crtc* crtcs; } ;
struct komeda_crtc {struct komeda_pipeline* slave; struct komeda_pipeline* master; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 

__attribute__((used)) static u32 get_possible_crtcs(struct komeda_kms_dev *kms,
			      struct komeda_pipeline *pipe)
{
	struct komeda_crtc *crtc;
	u32 possible_crtcs = 0;
	int i;

	for (i = 0; i < kms->n_crtcs; i++) {
		crtc = &kms->crtcs[i];

		if ((pipe == crtc->master) || (pipe == crtc->slave))
			possible_crtcs |= BIT(i);
	}

	return possible_crtcs;
}