#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int memcmd; struct dib9000_fe_memory_map* fe_mm; } ;
struct TYPE_4__ {TYPE_1__ risc; } ;
struct dib9000_state {TYPE_2__ platform; } ;
struct dib9000_fe_memory_map {int size; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib9000_risc_mem_setup_cmd (struct dib9000_state*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void dib9000_risc_mem_setup(struct dib9000_state *state, u8 cmd)
{
	struct dib9000_fe_memory_map *m = &state->platform.risc.fe_mm[cmd & 0x7f];
	/* decide whether we need to "refresh" the memory controller */
	if (state->platform.risc.memcmd == cmd &&	/* same command */
	    !(cmd & 0x80 && m->size < 67))	/* and we do not want to read something with less than 67 bytes looping - working around a bug in the memory controller */
		return;
	dib9000_risc_mem_setup_cmd(state, m->addr, m->size, cmd & 0x80);
	state->platform.risc.memcmd = cmd;
}