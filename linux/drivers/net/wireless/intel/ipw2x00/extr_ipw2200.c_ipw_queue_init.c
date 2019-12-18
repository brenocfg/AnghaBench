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
typedef  void* u32 ;
struct ipw_priv {int dummy; } ;
struct clx2_queue {int n_bd; int low_mark; int high_mark; int dma_addr; void* reg_w; void* reg_r; scalar_t__ last_used; scalar_t__ first_empty; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ipw_read32 (struct ipw_priv*,int) ; 
 int /*<<< orphan*/  ipw_write32 (struct ipw_priv*,void*,int) ; 

__attribute__((used)) static void ipw_queue_init(struct ipw_priv *priv, struct clx2_queue *q,
			   int count, u32 read, u32 write, u32 base, u32 size)
{
	q->n_bd = count;

	q->low_mark = q->n_bd / 4;
	if (q->low_mark < 4)
		q->low_mark = 4;

	q->high_mark = q->n_bd / 8;
	if (q->high_mark < 2)
		q->high_mark = 2;

	q->first_empty = q->last_used = 0;
	q->reg_r = read;
	q->reg_w = write;

	ipw_write32(priv, base, q->dma_addr);
	ipw_write32(priv, size, count);
	ipw_write32(priv, read, 0);
	ipw_write32(priv, write, 0);

	_ipw_read32(priv, 0x90);
}