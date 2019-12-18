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
struct TYPE_2__ {int lo; int hi; } ;
union l5cm_specific_data {TYPE_1__ phy_address; } ;
typedef  int u64 ;
typedef  size_t u32 ;
struct cnic_local {struct cnic_context* ctx_tbl; } ;
struct cnic_context {void* kwqe_data; scalar_t__ kwqe_data_mapping; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */

__attribute__((used)) static void *cnic_get_kwqe_16_data(struct cnic_local *cp, u32 l5_cid,
				   union l5cm_specific_data *l5_data)
{
	struct cnic_context *ctx = &cp->ctx_tbl[l5_cid];
	dma_addr_t map;

	map = ctx->kwqe_data_mapping;
	l5_data->phy_address.lo = (u64) map & 0xffffffff;
	l5_data->phy_address.hi = (u64) map >> 32;
	return ctx->kwqe_data;
}