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
struct imxdi_dev {unsigned int ioaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void di_write_busy_wait(const struct imxdi_dev *imxdi, u32 val,
			       unsigned reg)
{
	/* do the register write */
	writel(val, imxdi->ioaddr + reg);

	/*
	 * now it takes four 32,768 kHz clock cycles to take
	 * the change into effect = 122 us
	 */
	usleep_range(130, 200);
}