#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_2__ {int green; } ;
struct r8152 {TYPE_1__ ups_info; } ;

/* Variables and functions */
 int GREEN_ETH_EN ; 
 int SRAM_GREEN_CFG ; 
 int sram_read (struct r8152*,int) ; 
 int /*<<< orphan*/  sram_write (struct r8152*,int,int) ; 

__attribute__((used)) static void r8153b_green_en(struct r8152 *tp, bool enable)
{
	u16 data;

	if (enable) {
		sram_write(tp, 0x8045, 0);	/* 10M abiq&ldvbias */
		sram_write(tp, 0x804d, 0x1222);	/* 100M short abiq&ldvbias */
		sram_write(tp, 0x805d, 0x0022);	/* 1000M short abiq&ldvbias */
	} else {
		sram_write(tp, 0x8045, 0x2444);	/* 10M abiq&ldvbias */
		sram_write(tp, 0x804d, 0x2444);	/* 100M short abiq&ldvbias */
		sram_write(tp, 0x805d, 0x2444);	/* 1000M short abiq&ldvbias */
	}

	data = sram_read(tp, SRAM_GREEN_CFG);
	data |= GREEN_ETH_EN;
	sram_write(tp, SRAM_GREEN_CFG, data);

	tp->ups_info.green = enable;
}