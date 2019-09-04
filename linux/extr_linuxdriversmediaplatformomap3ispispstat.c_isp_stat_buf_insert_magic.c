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
typedef  scalar_t__ u32 ;
struct ispstat_buffer {scalar_t__ const virt_addr; } ;
struct ispstat {scalar_t__ buf_size; } ;

/* Variables and functions */
 scalar_t__ AF_EXTRA_DATA ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ IS_H3A_AF (struct ispstat*) ; 
 int /*<<< orphan*/  MAGIC_NUM ; 
 int /*<<< orphan*/  MAGIC_SIZE ; 
 int /*<<< orphan*/  isp_stat_buf_sync_magic_for_cpu (struct ispstat*,struct ispstat_buffer*,scalar_t__ const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_stat_buf_sync_magic_for_device (struct ispstat*,struct ispstat_buffer*,scalar_t__ const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__ const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isp_stat_buf_insert_magic(struct ispstat *stat,
				      struct ispstat_buffer *buf)
{
	const u32 buf_size = IS_H3A_AF(stat) ?
			     stat->buf_size + AF_EXTRA_DATA : stat->buf_size;

	isp_stat_buf_sync_magic_for_cpu(stat, buf, buf_size, DMA_FROM_DEVICE);

	/*
	 * Inserting MAGIC_NUM at the beginning and end of the buffer.
	 * buf->buf_size is set only after the buffer is queued. For now the
	 * right buf_size for the current configuration is pointed by
	 * stat->buf_size.
	 */
	memset(buf->virt_addr, MAGIC_NUM, MAGIC_SIZE);
	memset(buf->virt_addr + buf_size, MAGIC_NUM, MAGIC_SIZE);

	isp_stat_buf_sync_magic_for_device(stat, buf, buf_size,
					   DMA_BIDIRECTIONAL);
}