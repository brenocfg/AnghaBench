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
struct atusb {int dummy; } ;

/* Variables and functions */
 int atusb_read_reg (struct atusb*,unsigned int) ; 

__attribute__((used)) static int atusb_read_subreg(struct atusb *lp,
			     unsigned int addr, unsigned int mask,
			     unsigned int shift)
{
	int rc;

	rc = atusb_read_reg(lp, addr);
	rc = (rc & mask) >> shift;

	return rc;
}