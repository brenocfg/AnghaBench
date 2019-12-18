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
struct ptd {int /*<<< orphan*/  faddr; int /*<<< orphan*/  len; int /*<<< orphan*/  mps; int /*<<< orphan*/  count; } ;
struct isp116x_ep {int /*<<< orphan*/  length; int /*<<< orphan*/  data; struct isp116x_ep* active; struct ptd ptd; } ;
struct isp116x {scalar_t__ atl_last_dir; int atl_bufshrt; int atl_buflen; struct isp116x_ep* atl_active; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int HCATLPORT ; 
 int /*<<< orphan*/  HCXFERCTR ; 
 int /*<<< orphan*/  HCuPINT ; 
 int HCuPINT_AIIEOT ; 
 int ISP116x_WRITE_OFFSET ; 
 scalar_t__ PTD_DIR_IN ; 
 int /*<<< orphan*/  dump_ptd (struct ptd*) ; 
 int /*<<< orphan*/  dump_ptd_out_data (struct ptd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp116x_write_addr (struct isp116x*,int) ; 
 int /*<<< orphan*/  isp116x_write_data16 (struct isp116x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp116x_write_reg16 (struct isp116x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_ptddata_to_fifo (struct isp116x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pack_fifo(struct isp116x *isp116x)
{
	struct isp116x_ep *ep;
	struct ptd *ptd;
	int buflen = isp116x->atl_last_dir == PTD_DIR_IN
	    ? isp116x->atl_bufshrt : isp116x->atl_buflen;

	isp116x_write_reg16(isp116x, HCuPINT, HCuPINT_AIIEOT);
	isp116x_write_reg16(isp116x, HCXFERCTR, buflen);
	isp116x_write_addr(isp116x, HCATLPORT | ISP116x_WRITE_OFFSET);
	for (ep = isp116x->atl_active; ep; ep = ep->active) {
		ptd = &ep->ptd;
		dump_ptd(ptd);
		dump_ptd_out_data(ptd, ep->data);
		isp116x_write_data16(isp116x, ptd->count);
		isp116x_write_data16(isp116x, ptd->mps);
		isp116x_write_data16(isp116x, ptd->len);
		isp116x_write_data16(isp116x, ptd->faddr);
		buflen -= sizeof(struct ptd);
		/* Skip writing data for last IN PTD */
		if (ep->active || (isp116x->atl_last_dir != PTD_DIR_IN)) {
			write_ptddata_to_fifo(isp116x, ep->data, ep->length);
			buflen -= ALIGN(ep->length, 4);
		}
	}
	BUG_ON(buflen);
}