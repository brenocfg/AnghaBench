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
struct camif_vp {int /*<<< orphan*/  offset; int /*<<< orphan*/  id; int /*<<< orphan*/  camif; scalar_t__ vflip; scalar_t__ hflip; } ;

/* Variables and functions */
 int /*<<< orphan*/  CITRGFMT_FLIP_MASK ; 
 int /*<<< orphan*/  CITRGFMT_FLIP_X_MIRROR ; 
 int /*<<< orphan*/  CITRGFMT_FLIP_Y_MIRROR ; 
 int /*<<< orphan*/  S3C_CAMIF_REG_CITRGFMT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camif_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camif_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void camif_hw_set_flip(struct camif_vp *vp)
{
	u32 cfg = camif_read(vp->camif,
				S3C_CAMIF_REG_CITRGFMT(vp->id, vp->offset));

	cfg &= ~CITRGFMT_FLIP_MASK;

	if (vp->hflip)
		cfg |= CITRGFMT_FLIP_Y_MIRROR;
	if (vp->vflip)
		cfg |= CITRGFMT_FLIP_X_MIRROR;

	camif_write(vp->camif, S3C_CAMIF_REG_CITRGFMT(vp->id, vp->offset), cfg);
}