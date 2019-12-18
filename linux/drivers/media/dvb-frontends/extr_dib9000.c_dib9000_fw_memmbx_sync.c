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
typedef  scalar_t__ u8 ;
struct TYPE_3__ {int /*<<< orphan*/  fw_is_running; } ;
struct TYPE_4__ {TYPE_1__ risc; } ;
struct dib9000_state {scalar_t__* i2c_read_buffer; TYPE_2__ platform; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FE_MM_RW_SYNC ; 
 int /*<<< orphan*/  dib9000_risc_mem_read (struct dib9000_state*,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  dib9000_risc_mem_write (struct dib9000_state*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int dib9000_fw_memmbx_sync(struct dib9000_state *state, u8 i)
{
	u8 index_loop = 10;

	if (!state->platform.risc.fw_is_running)
		return 0;
	dib9000_risc_mem_write(state, FE_MM_RW_SYNC, &i);
	do {
		dib9000_risc_mem_read(state, FE_MM_RW_SYNC, state->i2c_read_buffer, 1);
	} while (state->i2c_read_buffer[0] && index_loop--);

	if (index_loop > 0)
		return 0;
	return -EIO;
}