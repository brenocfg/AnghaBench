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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {unsigned int max_sge_rd; } ;
struct ib_device {TYPE_1__ attrs; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 scalar_t__ rdma_rw_can_use_mr (struct ib_device*,int /*<<< orphan*/ ) ; 
 unsigned int rdma_rw_fr_page_list_len (struct ib_device*,int) ; 

unsigned int rdma_rw_mr_factor(struct ib_device *device, u8 port_num,
			       unsigned int maxpages)
{
	unsigned int mr_pages;

	if (rdma_rw_can_use_mr(device, port_num))
		mr_pages = rdma_rw_fr_page_list_len(device, false);
	else
		mr_pages = device->attrs.max_sge_rd;
	return DIV_ROUND_UP(maxpages, mr_pages);
}