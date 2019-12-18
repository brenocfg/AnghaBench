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
typedef  int /*<<< orphan*/  u_char ;
struct sym_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INB (struct sym_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T93C46_Clk (struct sym_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nc_gpreg ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void T93C46_Read_Bit(struct sym_device *np, u_char *read_bit, u_char *gpreg)
{
	udelay(2);
	T93C46_Clk(np, gpreg);
	*read_bit = INB(np, nc_gpreg);
}