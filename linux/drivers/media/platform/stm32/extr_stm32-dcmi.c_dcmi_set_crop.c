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
typedef  int u32 ;
struct TYPE_2__ {int height; int width; int top; int left; } ;
struct stm32_dcmi {int /*<<< orphan*/  regs; TYPE_1__ crop; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_CROP ; 
 int /*<<< orphan*/  DCMI_CR ; 
 int /*<<< orphan*/  DCMI_CWSIZE ; 
 int /*<<< orphan*/  DCMI_CWSTRT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  reg_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dcmi_set_crop(struct stm32_dcmi *dcmi)
{
	u32 size, start;

	/* Crop resolution */
	size = ((dcmi->crop.height - 1) << 16) |
		((dcmi->crop.width << 1) - 1);
	reg_write(dcmi->regs, DCMI_CWSIZE, size);

	/* Crop start point */
	start = ((dcmi->crop.top) << 16) |
		 ((dcmi->crop.left << 1));
	reg_write(dcmi->regs, DCMI_CWSTRT, start);

	dev_dbg(dcmi->dev, "Cropping to %ux%u@%u:%u\n",
		dcmi->crop.width, dcmi->crop.height,
		dcmi->crop.left, dcmi->crop.top);

	/* Enable crop */
	reg_set(dcmi->regs, DCMI_CR, CR_CROP);
}