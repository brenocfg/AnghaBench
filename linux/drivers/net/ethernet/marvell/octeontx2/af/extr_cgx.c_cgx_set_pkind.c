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
typedef  scalar_t__ u8 ;
struct cgx {scalar_t__ lmac_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGXX_CMRX_RX_ID_MAP ; 
 int ENODEV ; 
 int /*<<< orphan*/  cgx_write (struct cgx*,scalar_t__,int /*<<< orphan*/ ,int) ; 

int cgx_set_pkind(void *cgxd, u8 lmac_id, int pkind)
{
	struct cgx *cgx = cgxd;

	if (!cgx || lmac_id >= cgx->lmac_count)
		return -ENODEV;

	cgx_write(cgx, lmac_id, CGXX_CMRX_RX_ID_MAP, (pkind & 0x3F));
	return 0;
}