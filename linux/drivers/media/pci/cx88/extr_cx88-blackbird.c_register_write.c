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
typedef  int u32 ;
struct cx88_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  P1_RADDR0 ; 
 int /*<<< orphan*/  P1_RADDR1 ; 
 int /*<<< orphan*/  P1_RDATA0 ; 
 int /*<<< orphan*/  P1_RDATA1 ; 
 int /*<<< orphan*/  P1_RDATA2 ; 
 int /*<<< orphan*/  P1_RDATA3 ; 
 int /*<<< orphan*/  P1_RRDWR ; 
 int /*<<< orphan*/  cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_writeb (int /*<<< orphan*/ ,int) ; 
 int wait_ready_gpio0_bit1 (struct cx88_core*,int) ; 

__attribute__((used)) static int register_write(struct cx88_core *core, u32 address, u32 value)
{
	cx_writeb(P1_RDATA0, (unsigned int)value);
	cx_writeb(P1_RDATA1, (unsigned int)(value >> 8));
	cx_writeb(P1_RDATA2, (unsigned int)(value >> 16));
	cx_writeb(P1_RDATA3, (unsigned int)(value >> 24));
	cx_writeb(P1_RADDR0, (unsigned int)address);
	cx_writeb(P1_RADDR1, (unsigned int)(address >> 8));
	cx_writeb(P1_RRDWR, 1);
	cx_read(P1_RDATA0);
	cx_read(P1_RADDR0);

	return wait_ready_gpio0_bit1(core, 1);
}