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
typedef  int uint32_t ;
struct cx23885_dev {int dummy; } ;

/* Variables and functions */
 int ALT_AD_RG ; 
 int ALT_CS ; 
 int ALT_DATA ; 
 int ALT_RD ; 
 int ALT_RDY ; 
 int ALT_WR ; 
 int /*<<< orphan*/  MC417_OEN ; 
 int /*<<< orphan*/  MC417_RWD ; 
 int /*<<< orphan*/  cx_clear (int /*<<< orphan*/ ,int) ; 
 int cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int netup_altera_fpga_rw(void *device, int flag, int data, int read)
{
	struct cx23885_dev *dev = (struct cx23885_dev *)device;
	unsigned long timeout = jiffies + msecs_to_jiffies(1);
	uint32_t mem = 0;

	mem = cx_read(MC417_RWD);
	if (read)
		cx_set(MC417_OEN, ALT_DATA);
	else {
		cx_clear(MC417_OEN, ALT_DATA);/* D0-D7 out */
		mem &= ~ALT_DATA;
		mem |= (data & ALT_DATA);
	}

	if (flag)
		mem |= ALT_AD_RG;
	else
		mem &= ~ALT_AD_RG;

	mem &= ~ALT_CS;
	if (read)
		mem = (mem & ~ALT_RD) | ALT_WR;
	else
		mem = (mem & ~ALT_WR) | ALT_RD;

	cx_write(MC417_RWD, mem);  /* start RW cycle */

	for (;;) {
		mem = cx_read(MC417_RWD);
		if ((mem & ALT_RDY) == 0)
			break;
		if (time_after(jiffies, timeout))
			break;
		udelay(1);
	}

	cx_set(MC417_RWD, ALT_RD | ALT_WR | ALT_CS);
	if (read)
		return mem & ALT_DATA;

	return 0;
}