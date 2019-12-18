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
typedef  int u16 ;
struct brcms_hardware {int bmac_phytxant; } ;

/* Variables and functions */
 scalar_t__ C_CTX_PCTLWD_POS ; 
 scalar_t__ M_CTXPRS_BLK ; 
 scalar_t__ M_RSP_PCTLWD ; 
 int PHY_TXC_ANT_MASK ; 
 int brcms_b_read_shm (struct brcms_hardware*,scalar_t__) ; 
 int /*<<< orphan*/  brcms_b_write_shm (struct brcms_hardware*,scalar_t__,int) ; 

__attribute__((used)) static void brcms_c_ucode_txant_set(struct brcms_hardware *wlc_hw)
{
	u16 phyctl;
	u16 phytxant = wlc_hw->bmac_phytxant;
	u16 mask = PHY_TXC_ANT_MASK;

	/* set the Probe Response frame phy control word */
	phyctl = brcms_b_read_shm(wlc_hw, M_CTXPRS_BLK + C_CTX_PCTLWD_POS);
	phyctl = (phyctl & ~mask) | phytxant;
	brcms_b_write_shm(wlc_hw, M_CTXPRS_BLK + C_CTX_PCTLWD_POS, phyctl);

	/* set the Response (ACK/CTS) frame phy control word */
	phyctl = brcms_b_read_shm(wlc_hw, M_RSP_PCTLWD);
	phyctl = (phyctl & ~mask) | phytxant;
	brcms_b_write_shm(wlc_hw, M_RSP_PCTLWD, phyctl);
}