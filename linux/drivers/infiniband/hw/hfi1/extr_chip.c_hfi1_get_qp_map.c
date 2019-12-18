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
typedef  int u8 ;
typedef  int u64 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 scalar_t__ RCV_QP_MAP_TABLE ; 
 int read_csr (struct hfi1_devdata*,scalar_t__) ; 

u8 hfi1_get_qp_map(struct hfi1_devdata *dd, u8 idx)
{
	u64 reg = read_csr(dd, RCV_QP_MAP_TABLE + (idx / 8) * 8);

	reg >>= (idx % 8) * 8;
	return reg;
}