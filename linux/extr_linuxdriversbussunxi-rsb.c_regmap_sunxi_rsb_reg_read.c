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
struct sunxi_rsb_device {int /*<<< orphan*/  rtaddr; int /*<<< orphan*/  rsb; } ;
struct sunxi_rsb_ctx {int /*<<< orphan*/  size; struct sunxi_rsb_device* rdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int sunxi_rsb_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int regmap_sunxi_rsb_reg_read(void *context, unsigned int reg,
				     unsigned int *val)
{
	struct sunxi_rsb_ctx *ctx = context;
	struct sunxi_rsb_device *rdev = ctx->rdev;

	if (reg > 0xff)
		return -EINVAL;

	return sunxi_rsb_read(rdev->rsb, rdev->rtaddr, reg, val, ctx->size);
}