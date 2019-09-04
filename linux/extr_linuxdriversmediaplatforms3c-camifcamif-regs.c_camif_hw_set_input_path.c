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
struct camif_vp {int /*<<< orphan*/  id; int /*<<< orphan*/  camif; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSCTRL_SEL_DMA_CAM ; 
 int /*<<< orphan*/  S3C_CAMIF_REG_MSCTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camif_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camif_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void camif_hw_set_input_path(struct camif_vp *vp)
{
	u32 cfg = camif_read(vp->camif, S3C_CAMIF_REG_MSCTRL(vp->id));
	cfg &= ~MSCTRL_SEL_DMA_CAM;
	camif_write(vp->camif, S3C_CAMIF_REG_MSCTRL(vp->id), cfg);
}