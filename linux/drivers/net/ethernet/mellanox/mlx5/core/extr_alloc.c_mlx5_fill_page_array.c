#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct mlx5_frag_buf {int npages; int page_shift; TYPE_1__* frags; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_2__ {scalar_t__ map; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 

void mlx5_fill_page_array(struct mlx5_frag_buf *buf, __be64 *pas)
{
	u64 addr;
	int i;

	for (i = 0; i < buf->npages; i++) {
		addr = buf->frags->map + (i << buf->page_shift);

		pas[i] = cpu_to_be64(addr);
	}
}