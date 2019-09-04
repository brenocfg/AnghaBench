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
struct ks_net {int enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS_RXCR1 ; 
 int /*<<< orphan*/  KS_RXQCR ; 
 int /*<<< orphan*/  KS_TXCR ; 
 int RXCR1_RXE ; 
 int RXQCR_RXFCTE ; 
 int TXCR_TXE ; 
 int ks_rdreg16 (struct ks_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_wrreg16 (struct ks_net*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ks_enable_qmu(struct ks_net *ks)
{
	u16 w;

	w = ks_rdreg16(ks, KS_TXCR);
	/* Enables QMU Transmit (TXCR). */
	ks_wrreg16(ks, KS_TXCR, w | TXCR_TXE);

	/*
	 * RX Frame Count Threshold Enable and Auto-Dequeue RXQ Frame
	 * Enable
	 */

	w = ks_rdreg16(ks, KS_RXQCR);
	ks_wrreg16(ks, KS_RXQCR, w | RXQCR_RXFCTE);

	/* Enables QMU Receive (RXCR1). */
	w = ks_rdreg16(ks, KS_RXCR1);
	ks_wrreg16(ks, KS_RXCR1, w | RXCR1_RXE);
	ks->enabled = true;
}