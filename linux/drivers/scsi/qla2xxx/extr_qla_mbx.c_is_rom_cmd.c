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
typedef  scalar_t__ uint16_t ;
struct rom_cmd {scalar_t__ cmd; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct rom_cmd*) ; 
 struct rom_cmd* rom_cmds ; 

__attribute__((used)) static int is_rom_cmd(uint16_t cmd)
{
	int i;
	struct  rom_cmd *wc;

	for (i = 0; i < ARRAY_SIZE(rom_cmds); i++) {
		wc = rom_cmds + i;
		if (wc->cmd == cmd)
			return 1;
	}

	return 0;
}