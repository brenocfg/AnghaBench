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
struct emmaprp_dev {scalar_t__ base_emma; } ;

/* Variables and functions */
 scalar_t__ PRP_CH2_OUT_IMAGE_SIZE ; 
 scalar_t__ PRP_CNTL ; 
 scalar_t__ PRP_DEST_CB_PTR ; 
 scalar_t__ PRP_DEST_CR_PTR ; 
 scalar_t__ PRP_DEST_Y_PTR ; 
 scalar_t__ PRP_SOURCE_Y_PTR ; 
 scalar_t__ PRP_SRC_FRAME_SIZE ; 
 int /*<<< orphan*/  dprintk (struct emmaprp_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static inline void emmaprp_dump_regs(struct emmaprp_dev *pcdev)
{
	dprintk(pcdev,
		"eMMa-PrP Registers:\n"
		"  SOURCE_Y_PTR = 0x%08X\n"
		"  SRC_FRAME_SIZE = 0x%08X\n"
		"  DEST_Y_PTR = 0x%08X\n"
		"  DEST_CR_PTR = 0x%08X\n"
		"  DEST_CB_PTR = 0x%08X\n"
		"  CH2_OUT_IMAGE_SIZE = 0x%08X\n"
		"  CNTL = 0x%08X\n",
		readl(pcdev->base_emma + PRP_SOURCE_Y_PTR),
		readl(pcdev->base_emma + PRP_SRC_FRAME_SIZE),
		readl(pcdev->base_emma + PRP_DEST_Y_PTR),
		readl(pcdev->base_emma + PRP_DEST_CR_PTR),
		readl(pcdev->base_emma + PRP_DEST_CB_PTR),
		readl(pcdev->base_emma + PRP_CH2_OUT_IMAGE_SIZE),
		readl(pcdev->base_emma + PRP_CNTL));
}