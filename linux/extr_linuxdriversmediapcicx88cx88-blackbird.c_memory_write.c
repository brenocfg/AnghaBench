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
 int /*<<< orphan*/  P1_MADDR0 ; 
 int /*<<< orphan*/  P1_MADDR1 ; 
 int /*<<< orphan*/  P1_MADDR2 ; 
 int /*<<< orphan*/  P1_MDATA0 ; 
 int /*<<< orphan*/  P1_MDATA1 ; 
 int /*<<< orphan*/  P1_MDATA2 ; 
 int /*<<< orphan*/  P1_MDATA3 ; 
 int /*<<< orphan*/  cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_writeb (int /*<<< orphan*/ ,unsigned int) ; 
 int wait_ready_gpio0_bit1 (struct cx88_core*,int) ; 

__attribute__((used)) static int memory_write(struct cx88_core *core, u32 address, u32 value)
{
	/* Warning: address is dword address (4 bytes) */
	cx_writeb(P1_MDATA0, (unsigned int)value);
	cx_writeb(P1_MDATA1, (unsigned int)(value >> 8));
	cx_writeb(P1_MDATA2, (unsigned int)(value >> 16));
	cx_writeb(P1_MDATA3, (unsigned int)(value >> 24));
	cx_writeb(P1_MADDR2, (unsigned int)(address >> 16) | 0x40);
	cx_writeb(P1_MADDR1, (unsigned int)(address >> 8));
	cx_writeb(P1_MADDR0, (unsigned int)address);
	cx_read(P1_MDATA0);
	cx_read(P1_MADDR0);

	return wait_ready_gpio0_bit1(core, 1);
}