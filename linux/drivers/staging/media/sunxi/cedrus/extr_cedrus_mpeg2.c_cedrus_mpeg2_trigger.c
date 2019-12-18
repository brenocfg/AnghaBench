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
typedef  int u32 ;
struct cedrus_dev {int dummy; } ;
struct cedrus_ctx {struct cedrus_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VE_DEC_MPEG_TRIGGER ; 
 int VE_DEC_MPEG_TRIGGER_HW_MPEG_VLD ; 
 int VE_DEC_MPEG_TRIGGER_MB_BOUNDARY ; 
 int VE_DEC_MPEG_TRIGGER_MPEG2 ; 
 int /*<<< orphan*/  cedrus_write (struct cedrus_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cedrus_mpeg2_trigger(struct cedrus_ctx *ctx)
{
	struct cedrus_dev *dev = ctx->dev;
	u32 reg;

	/* Trigger MPEG engine. */
	reg = VE_DEC_MPEG_TRIGGER_HW_MPEG_VLD | VE_DEC_MPEG_TRIGGER_MPEG2 |
	      VE_DEC_MPEG_TRIGGER_MB_BOUNDARY;

	cedrus_write(dev, VE_DEC_MPEG_TRIGGER, reg);
}