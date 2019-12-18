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
struct dma_fifo {int avail; int in; int capacity; int /*<<< orphan*/  done; int /*<<< orphan*/  out; scalar_t__ data; scalar_t__ corrupt; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENXIO ; 
 scalar_t__ FAIL (struct dma_fifo*,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ addr_check (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  df_trace (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,int) ; 
 int min (int,int) ; 

int dma_fifo_in(struct dma_fifo *fifo, const void *src, int n)
{
	int ofs, l;

	if (!fifo->data)
		return -ENOENT;
	if (fifo->corrupt)
		return -ENXIO;

	if (n > fifo->avail)
		n = fifo->avail;
	if (n <= 0)
		return 0;

	ofs = fifo->in % fifo->capacity;
	l = min(n, fifo->capacity - ofs);
	memcpy(fifo->data + ofs, src, l);
	memcpy(fifo->data, src + l, n - l);

	if (FAIL(fifo, addr_check(fifo->done, fifo->in, fifo->in + n) ||
		 fifo->avail < n,
		 "fifo corrupt: in:%u out:%u done:%u n:%d avail:%d",
		 fifo->in, fifo->out, fifo->done, n, fifo->avail))
		return -ENXIO;

	fifo->in += n;
	fifo->avail -= n;

	df_trace("in:%u out:%u done:%u n:%d avail:%d", fifo->in, fifo->out,
		 fifo->done, n, fifo->avail);

	return n;
}