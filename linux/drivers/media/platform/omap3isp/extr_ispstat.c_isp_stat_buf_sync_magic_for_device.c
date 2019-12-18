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
typedef  int /*<<< orphan*/  u32 ;
struct ispstat_buffer {int dummy; } ;
struct ispstat {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 scalar_t__ ISP_STAT_USES_DMAENGINE (struct ispstat*) ; 
 int /*<<< orphan*/  __isp_stat_buf_sync_magic (struct ispstat*,struct ispstat_buffer*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_range_for_device ; 

__attribute__((used)) static void isp_stat_buf_sync_magic_for_device(struct ispstat *stat,
					       struct ispstat_buffer *buf,
					       u32 buf_size,
					       enum dma_data_direction dir)
{
	if (ISP_STAT_USES_DMAENGINE(stat))
		return;

	__isp_stat_buf_sync_magic(stat, buf, buf_size, dir,
				  dma_sync_single_range_for_device);
}