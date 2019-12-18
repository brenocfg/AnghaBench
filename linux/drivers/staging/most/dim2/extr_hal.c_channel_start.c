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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct int_ch_state {unsigned int level; int idx1; } ;
struct dim_channel {scalar_t__ packet_length; scalar_t__ bytes_per_frame; scalar_t__ addr; struct int_ch_state state; } ;
struct TYPE_3__ {scalar_t__ ch_addr; } ;
struct TYPE_4__ {TYPE_1__ atx_dbr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIM_ERR_BAD_BUFFER_SIZE ; 
 int /*<<< orphan*/  DIM_ERR_OVERFLOW ; 
 int /*<<< orphan*/  dbrcnt_enq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dim2_start_ctrl_async (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dim2_start_isoc_sync (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dim_norm_ctrl_async_buffer_size (int /*<<< orphan*/ ) ; 
 int dim_on_error (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ g ; 
 int /*<<< orphan*/  norm_isoc_buffer_size (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  norm_sync_buffer_size (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool channel_start(struct dim_channel *ch, u32 buf_addr, u16 buf_size)
{
	struct int_ch_state *const state = &ch->state;

	if (buf_size <= 0)
		return dim_on_error(DIM_ERR_BAD_BUFFER_SIZE, "Bad buffer size");

	if (ch->packet_length == 0 && ch->bytes_per_frame == 0 &&
	    buf_size != dim_norm_ctrl_async_buffer_size(buf_size))
		return dim_on_error(DIM_ERR_BAD_BUFFER_SIZE,
				    "Bad control/async buffer size");

	if (ch->packet_length &&
	    buf_size != norm_isoc_buffer_size(buf_size, ch->packet_length))
		return dim_on_error(DIM_ERR_BAD_BUFFER_SIZE,
				    "Bad isochronous buffer size");

	if (ch->bytes_per_frame &&
	    buf_size != norm_sync_buffer_size(buf_size, ch->bytes_per_frame))
		return dim_on_error(DIM_ERR_BAD_BUFFER_SIZE,
				    "Bad synchronous buffer size");

	if (state->level >= 2u)
		return dim_on_error(DIM_ERR_OVERFLOW, "Channel overflow");

	++state->level;

	if (ch->addr == g.atx_dbr.ch_addr)
		dbrcnt_enq(buf_size);

	if (ch->packet_length || ch->bytes_per_frame)
		dim2_start_isoc_sync(ch->addr, state->idx1, buf_addr, buf_size);
	else
		dim2_start_ctrl_async(ch->addr, state->idx1, buf_addr,
				      buf_size);
	state->idx1 ^= 1;

	return true;
}