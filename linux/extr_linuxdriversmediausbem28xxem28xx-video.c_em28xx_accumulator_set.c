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
typedef  int /*<<< orphan*/  u8 ;
struct em28xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EM28XX_R28_XMIN ; 
 int /*<<< orphan*/  EM28XX_R29_XMAX ; 
 int /*<<< orphan*/  EM28XX_R2A_YMIN ; 
 int /*<<< orphan*/  EM28XX_R2B_YMAX ; 
 int /*<<< orphan*/  em28xx_videodbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int em28xx_write_regs (struct em28xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int em28xx_accumulator_set(struct em28xx *dev, u8 xmin, u8 xmax,
				  u8 ymin, u8 ymax)
{
	em28xx_videodbg("em28xx Scale: (%d,%d)-(%d,%d)\n",
			xmin, ymin, xmax, ymax);

	em28xx_write_regs(dev, EM28XX_R28_XMIN, &xmin, 1);
	em28xx_write_regs(dev, EM28XX_R29_XMAX, &xmax, 1);
	em28xx_write_regs(dev, EM28XX_R2A_YMIN, &ymin, 1);
	return em28xx_write_regs(dev, EM28XX_R2B_YMAX, &ymax, 1);
}