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
typedef  int u16 ;
struct etnaviv_cmdbuf {int user_size; } ;
struct etnaviv_gpu {int /*<<< orphan*/  lock; struct etnaviv_cmdbuf buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_LINK (struct etnaviv_cmdbuf*,int,scalar_t__) ; 
 int /*<<< orphan*/  CMD_WAIT (struct etnaviv_cmdbuf*) ; 
 scalar_t__ etnaviv_cmdbuf_get_va (struct etnaviv_cmdbuf*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

u16 etnaviv_buffer_init(struct etnaviv_gpu *gpu)
{
	struct etnaviv_cmdbuf *buffer = &gpu->buffer;

	lockdep_assert_held(&gpu->lock);

	/* initialize buffer */
	buffer->user_size = 0;

	CMD_WAIT(buffer);
	CMD_LINK(buffer, 2, etnaviv_cmdbuf_get_va(buffer) +
		 buffer->user_size - 4);

	return buffer->user_size / 8;
}