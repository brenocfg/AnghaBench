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
 int /*<<< orphan*/  OUTB (struct sym_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S24C16_do_bit (struct sym_device*,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  nc_gpcntl ; 

__attribute__((used)) static void S24C16_write_ack(struct sym_device *np, u_char write_bit, u_char *gpreg, 
			    u_char *gpcntl)
{
	OUTB(np, nc_gpcntl, *gpcntl & 0xfe);
	S24C16_do_bit(np, NULL, write_bit, gpreg);
	OUTB(np, nc_gpcntl, *gpcntl);
}