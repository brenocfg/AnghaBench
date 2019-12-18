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
struct imx355 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX355_MODE_STANDBY ; 
 int /*<<< orphan*/  IMX355_REG_MODE_SELECT ; 
 int imx355_write_reg (struct imx355*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx355_stop_streaming(struct imx355 *imx355)
{
	return imx355_write_reg(imx355, IMX355_REG_MODE_SELECT,
				1, IMX355_MODE_STANDBY);
}