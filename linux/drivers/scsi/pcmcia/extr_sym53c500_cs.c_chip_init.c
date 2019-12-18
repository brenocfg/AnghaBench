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

/* Variables and functions */
 int C1_IMG ; 
 int C2_IMG ; 
 int C3_IMG ; 
 int C4_IMG ; 
 int CLKCONV ; 
 int CONFIG1 ; 
 int CONFIG2 ; 
 int CONFIG3 ; 
 int CONFIG4 ; 
 int PIO_FLAG ; 
 int PIO_STATUS ; 
 int /*<<< orphan*/  REG1 (int) ; 
 int SRTIMOUT ; 
 int SYNCOFF ; 
 int SYNCPRD ; 
 int SYNC_MODE ; 
 int /*<<< orphan*/  outb (int,int) ; 

__attribute__((used)) static void
chip_init(int io_port)
{
	REG1(io_port);
	outb(0x01, io_port + PIO_STATUS);
	outb(0x00, io_port + PIO_FLAG);

	outb(C4_IMG, io_port + CONFIG4);	/* REG0(io_port); */
	outb(C3_IMG, io_port + CONFIG3);
	outb(C2_IMG, io_port + CONFIG2);
	outb(C1_IMG, io_port + CONFIG1);

	outb(0x05, io_port + CLKCONV);	/* clock conversion factor */
	outb(0x9C, io_port + SRTIMOUT);	/* Selection timeout */
	outb(0x05, io_port + SYNCPRD);	/* Synchronous transfer period */
	outb(SYNC_MODE, io_port + SYNCOFF);	/* synchronous mode */  
}