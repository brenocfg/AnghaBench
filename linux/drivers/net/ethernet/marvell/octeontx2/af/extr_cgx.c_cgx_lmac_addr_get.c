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
struct cgx {int dummy; } ;

/* Variables and functions */
 scalar_t__ CGXX_CMRX_RX_DMAC_CAM0 ; 
 int CGX_RX_DMAC_ADR_MASK ; 
 struct cgx* cgx_get_pdata (int) ; 
 int cgx_read (struct cgx*,int /*<<< orphan*/ ,scalar_t__) ; 

u64 cgx_lmac_addr_get(u8 cgx_id, u8 lmac_id)
{
	struct cgx *cgx_dev = cgx_get_pdata(cgx_id);
	u64 cfg;

	cfg = cgx_read(cgx_dev, 0, CGXX_CMRX_RX_DMAC_CAM0 + lmac_id * 0x8);
	return cfg & CGX_RX_DMAC_ADR_MASK;
}