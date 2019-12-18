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
typedef  int u32 ;
struct ispstat_buffer {int buf_size; scalar_t__* virt_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct ispstat {TYPE_2__ subdev; TYPE_1__* isp; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AF_EXTRA_DATA ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EINVAL ; 
 scalar_t__ IS_H3A_AF (struct ispstat*) ; 
 scalar_t__ MAGIC_NUM ; 
 int MAGIC_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_stat_buf_sync_magic_for_cpu (struct ispstat*,struct ispstat_buffer*,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_stat_buf_sync_magic_for_device (struct ispstat*,struct ispstat_buffer*,int const,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int isp_stat_buf_check_magic(struct ispstat *stat,
				    struct ispstat_buffer *buf)
{
	const u32 buf_size = IS_H3A_AF(stat) ?
			     buf->buf_size + AF_EXTRA_DATA : buf->buf_size;
	u8 *w;
	u8 *end;
	int ret = -EINVAL;

	isp_stat_buf_sync_magic_for_cpu(stat, buf, buf_size, DMA_FROM_DEVICE);

	/* Checking initial magic numbers. They shouldn't be here anymore. */
	for (w = buf->virt_addr, end = w + MAGIC_SIZE; w < end; w++)
		if (likely(*w != MAGIC_NUM))
			ret = 0;

	if (ret) {
		dev_dbg(stat->isp->dev,
			"%s: beginning magic check does not match.\n",
			stat->subdev.name);
		return ret;
	}

	/* Checking magic numbers at the end. They must be still here. */
	for (w = buf->virt_addr + buf_size, end = w + MAGIC_SIZE;
	     w < end; w++) {
		if (unlikely(*w != MAGIC_NUM)) {
			dev_dbg(stat->isp->dev,
				"%s: ending magic check does not match.\n",
				stat->subdev.name);
			return -EINVAL;
		}
	}

	isp_stat_buf_sync_magic_for_device(stat, buf, buf_size,
					   DMA_FROM_DEVICE);

	return 0;
}