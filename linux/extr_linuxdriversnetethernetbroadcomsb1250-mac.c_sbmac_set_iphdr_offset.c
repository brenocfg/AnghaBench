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
typedef  int uint64_t ;
struct sbmac_softc {int /*<<< orphan*/  rx_hw_checksum; int /*<<< orphan*/  sbm_rxfilter; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLE ; 
 int /*<<< orphan*/  ENABLE ; 
 scalar_t__ K_SYS_SOC_TYPE_BCM1250 ; 
 int M_MAC_IPHDR_OFFSET ; 
 int V_MAC_IPHDR_OFFSET (int) ; 
 int __raw_readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writeq (int,int /*<<< orphan*/ ) ; 
 int periph_rev ; 
 scalar_t__ soc_type ; 

__attribute__((used)) static void sbmac_set_iphdr_offset(struct sbmac_softc *sc)
{
	uint64_t reg;

	/* Hard code the off set to 15 for now */
	reg = __raw_readq(sc->sbm_rxfilter);
	reg &= ~M_MAC_IPHDR_OFFSET | V_MAC_IPHDR_OFFSET(15);
	__raw_writeq(reg, sc->sbm_rxfilter);

	/* BCM1250 pass1 didn't have hardware checksum.  Everything
	   later does.  */
	if (soc_type == K_SYS_SOC_TYPE_BCM1250 && periph_rev < 2) {
		sc->rx_hw_checksum = DISABLE;
	} else {
		sc->rx_hw_checksum = ENABLE;
	}
}