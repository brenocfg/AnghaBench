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
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;
struct mlx4_buf {int nbufs; int npages; unsigned long page_shift; TYPE_2__* page_list; TYPE_1__ direct; } ;
struct TYPE_4__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,unsigned long) ; 

__attribute__((used)) static void mlx4_init_kernel_cqes(struct mlx4_buf *buf,
				  int entries,
				  int cqe_size)
{
	int i;

	if (buf->nbufs == 1)
		memset(buf->direct.buf, 0xcc, entries * cqe_size);
	else
		for (i = 0; i < buf->npages; i++)
			memset(buf->page_list[i].buf, 0xcc,
			       1UL << buf->page_shift);
}