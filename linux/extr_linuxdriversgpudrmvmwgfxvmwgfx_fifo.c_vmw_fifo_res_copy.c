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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct vmw_fifo_state {int* dynamic_buffer; int* static_buffer; } ;

/* Variables and functions */
 int SVGA_FIFO_RESERVED ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  vmw_mmio_write (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vmw_fifo_res_copy(struct vmw_fifo_state *fifo_state,
			      u32  *fifo_mem,
			      uint32_t next_cmd,
			      uint32_t max, uint32_t min, uint32_t bytes)
{
	uint32_t chunk_size = max - next_cmd;
	uint32_t rest;
	uint32_t *buffer = (fifo_state->dynamic_buffer != NULL) ?
	    fifo_state->dynamic_buffer : fifo_state->static_buffer;

	if (bytes < chunk_size)
		chunk_size = bytes;

	vmw_mmio_write(bytes, fifo_mem + SVGA_FIFO_RESERVED);
	mb();
	memcpy(fifo_mem + (next_cmd >> 2), buffer, chunk_size);
	rest = bytes - chunk_size;
	if (rest)
		memcpy(fifo_mem + (min >> 2), buffer + (chunk_size >> 2), rest);
}