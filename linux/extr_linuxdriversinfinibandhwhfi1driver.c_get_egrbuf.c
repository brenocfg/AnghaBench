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
typedef  int u8 ;
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct TYPE_4__ {int threshold; TYPE_1__* rcvtids; } ;
struct hfi1_ctxtdata {TYPE_2__ egrbufs; } ;
struct TYPE_3__ {scalar_t__ addr; } ;

/* Variables and functions */
 int RCV_BUF_BLOCK_SIZE ; 
 int rhf_egr_buf_offset (scalar_t__) ; 
 int rhf_egr_index (scalar_t__) ; 

__attribute__((used)) static inline void *get_egrbuf(const struct hfi1_ctxtdata *rcd, u64 rhf,
			       u8 *update)
{
	u32 idx = rhf_egr_index(rhf), offset = rhf_egr_buf_offset(rhf);

	*update |= !(idx & (rcd->egrbufs.threshold - 1)) && !offset;
	return (void *)(((u64)(rcd->egrbufs.rcvtids[idx].addr)) +
			(offset * RCV_BUF_BLOCK_SIZE));
}