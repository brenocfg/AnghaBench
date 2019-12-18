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
struct imx21 {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ USB_ETD_DWORD (int,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void etd_writel(struct imx21 *imx21, int etd_num, int dword, u32 value)
{
	writel(value, imx21->regs + USB_ETD_DWORD(etd_num, dword));
}