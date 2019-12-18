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
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  CMD_END (struct etnaviv_cmdbuf*) ; 
 int /*<<< orphan*/  CMD_LOAD_STATE (struct etnaviv_cmdbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIVS_MMUv2_PTA_CONFIG ; 
 int /*<<< orphan*/  VIVS_MMUv2_PTA_CONFIG_INDEX (unsigned short) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

u16 etnaviv_buffer_config_pta(struct etnaviv_gpu *gpu, unsigned short id)
{
	struct etnaviv_cmdbuf *buffer = &gpu->buffer;

	lockdep_assert_held(&gpu->lock);

	buffer->user_size = 0;

	CMD_LOAD_STATE(buffer, VIVS_MMUv2_PTA_CONFIG,
		       VIVS_MMUv2_PTA_CONFIG_INDEX(id));

	CMD_END(buffer);

	buffer->user_size = ALIGN(buffer->user_size, 8);

	return buffer->user_size / 8;
}