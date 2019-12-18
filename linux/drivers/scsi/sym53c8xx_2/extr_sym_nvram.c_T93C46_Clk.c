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
typedef  int u_char ;
struct sym_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INB (struct sym_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTB (struct sym_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nc_gpreg ; 
 int /*<<< orphan*/  nc_mbox1 ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void T93C46_Clk(struct sym_device *np, u_char *gpreg)
{
	OUTB(np, nc_gpreg, *gpreg | 0x04);
	INB(np, nc_mbox1);
	udelay(2);
	OUTB(np, nc_gpreg, *gpreg);
}