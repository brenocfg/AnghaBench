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
struct s5p_mfc_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ofs; } ;
struct s5p_mfc_ctx {TYPE_1__ shm; struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  S5P_FIMV_SI_CH0_HOST_WR_ADR ; 
 int /*<<< orphan*/  mfc_write (struct s5p_mfc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s5p_mfc_set_shared_buffer(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	mfc_write(dev, ctx->shm.ofs, S5P_FIMV_SI_CH0_HOST_WR_ADR);
}