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
typedef  int u8 ;
struct cx23885_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  F300_CLK ; 
 int /*<<< orphan*/  F300_DATA ; 
 int f300_get_line (struct cx23885_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f300_set_line (struct cx23885_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u8 f300_get_byte(struct cx23885_dev *dev)
{
	u8 i, dta = 0;

	for (i = 0; i < 8; i++) {
		f300_set_line(dev, F300_CLK, 0);
		udelay(30);
		dta <<= 1;
		f300_set_line(dev, F300_CLK, 1);
		udelay(30);
		dta |= f300_get_line(dev, F300_DATA);/* msb first */

	}

	return dta;
}