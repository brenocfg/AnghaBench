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
struct cedrus_dev {int dummy; } ;
struct cedrus_ctx {struct cedrus_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VE_DEC_MPEG_CTRL ; 
 int /*<<< orphan*/  VE_DEC_MPEG_CTRL_IRQ_MASK ; 
 int /*<<< orphan*/  cedrus_read (struct cedrus_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cedrus_write (struct cedrus_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cedrus_mpeg2_irq_disable(struct cedrus_ctx *ctx)
{
	struct cedrus_dev *dev = ctx->dev;
	u32 reg = cedrus_read(dev, VE_DEC_MPEG_CTRL);

	reg &= ~VE_DEC_MPEG_CTRL_IRQ_MASK;

	cedrus_write(dev, VE_DEC_MPEG_CTRL, reg);
}