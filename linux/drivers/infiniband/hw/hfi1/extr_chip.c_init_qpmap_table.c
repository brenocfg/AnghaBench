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
typedef  int u64 ;
typedef  int u32 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int RCV_CTRL_RCV_BYPASS_ENABLE_SMASK ; 
 int RCV_CTRL_RCV_QP_MAP_ENABLE_SMASK ; 
 int RCV_QP_MAP_TABLE ; 
 int /*<<< orphan*/  add_rcvctrl (struct hfi1_devdata*,int) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int,int) ; 

__attribute__((used)) static void init_qpmap_table(struct hfi1_devdata *dd,
			     u32 first_ctxt,
			     u32 last_ctxt)
{
	u64 reg = 0;
	u64 regno = RCV_QP_MAP_TABLE;
	int i;
	u64 ctxt = first_ctxt;

	for (i = 0; i < 256; i++) {
		reg |= ctxt << (8 * (i % 8));
		ctxt++;
		if (ctxt > last_ctxt)
			ctxt = first_ctxt;
		if (i % 8 == 7) {
			write_csr(dd, regno, reg);
			reg = 0;
			regno += 8;
		}
	}

	add_rcvctrl(dd, RCV_CTRL_RCV_QP_MAP_ENABLE_SMASK
			| RCV_CTRL_RCV_BYPASS_ENABLE_SMASK);
}