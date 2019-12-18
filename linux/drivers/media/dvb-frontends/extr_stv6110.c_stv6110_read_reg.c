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
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stv6110_read_regs (struct dvb_frontend*,int*,int,int) ; 

__attribute__((used)) static int stv6110_read_reg(struct dvb_frontend *fe, int start)
{
	u8 buf[] = { 0 };
	stv6110_read_regs(fe, buf, start, 1);

	return buf[0];
}