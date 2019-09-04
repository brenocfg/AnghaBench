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
typedef  unsigned int u8 ;
struct mchp23k256_flash {TYPE_1__* caps; } ;
struct TYPE_2__ {int addr_width; } ;

/* Variables and functions */

__attribute__((used)) static void mchp23k256_addr2cmd(struct mchp23k256_flash *flash,
				unsigned int addr, u8 *cmd)
{
	int i;

	/*
	 * Address is sent in big endian (MSB first) and we skip
	 * the first entry of the cmd array which contains the cmd
	 * opcode.
	 */
	for (i = flash->caps->addr_width; i > 0; i--, addr >>= 8)
		cmd[i] = addr;
}