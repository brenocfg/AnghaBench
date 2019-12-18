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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {scalar_t__ IO_ADDR_W; scalar_t__ IO_ADDR_R; } ;
struct nand_chip {TYPE_1__ legacy; } ;

/* Variables and functions */
 int CS_NAND_CTLR_BUSY ; 
 scalar_t__ MM_NAND_STS ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void cs553x_write_byte(struct nand_chip *this, u_char byte)
{
	int i = 100000;

	while (i && readb(this->legacy.IO_ADDR_R + MM_NAND_STS) & CS_NAND_CTLR_BUSY) {
		udelay(1);
		i--;
	}
	writeb(byte, this->legacy.IO_ADDR_W + 0x801);
}