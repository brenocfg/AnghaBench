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
struct ptd {int dummy; } ;
struct isp1362_hcd {int dummy; } ;
struct isp1362_ep_queue {int dummy; } ;
struct isp1362_ep {int length; int ptd_offset; struct ptd* data; struct ptd ptd; } ;

/* Variables and functions */
 scalar_t__ PTD_DIR_IN ; 
 scalar_t__ PTD_GET_DIR (struct ptd*) ; 
 int PTD_HEADER_SIZE ; 
 int /*<<< orphan*/  dump_ptd (struct ptd*) ; 
 int /*<<< orphan*/  dump_ptd_out_data (struct ptd*,struct ptd*) ; 
 int /*<<< orphan*/  isp1362_write_buffer (struct isp1362_hcd*,struct ptd*,int,int) ; 
 int /*<<< orphan*/  prefetch (struct ptd*) ; 

__attribute__((used)) static void isp1362_write_ptd(struct isp1362_hcd *isp1362_hcd, struct isp1362_ep *ep,
			      struct isp1362_ep_queue *epq)
{
	struct ptd *ptd = &ep->ptd;
	int len = PTD_GET_DIR(ptd) == PTD_DIR_IN ? 0 : ep->length;

	prefetch(ptd);
	isp1362_write_buffer(isp1362_hcd, ptd, ep->ptd_offset, PTD_HEADER_SIZE);
	if (len)
		isp1362_write_buffer(isp1362_hcd, ep->data,
				     ep->ptd_offset + PTD_HEADER_SIZE, len);

	dump_ptd(ptd);
	dump_ptd_out_data(ptd, ep->data);
}