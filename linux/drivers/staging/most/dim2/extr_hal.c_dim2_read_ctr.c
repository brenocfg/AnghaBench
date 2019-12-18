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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_4__ {TYPE_1__* dim2; } ;
struct TYPE_3__ {int /*<<< orphan*/  MDAT0; } ;

/* Variables and functions */
 int /*<<< orphan*/  dim2_transfer_madr (int /*<<< orphan*/ ) ; 
 TYPE_2__ g ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 dim2_read_ctr(u32 ctr_addr, u16 mdat_idx)
{
	dim2_transfer_madr(ctr_addr);

	return readl((&g.dim2->MDAT0) + mdat_idx);
}