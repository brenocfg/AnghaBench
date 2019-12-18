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
typedef  unsigned int u32 ;
struct TYPE_2__ {scalar_t__ virt; } ;
struct s5p_mfc_ctx {TYPE_1__ shm; } ;

/* Variables and functions */
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static unsigned int s5p_mfc_read_info_v5(struct s5p_mfc_ctx *ctx,
				unsigned long ofs)
{
	rmb();
	return *(u32 *)(ctx->shm.virt + ofs);
}