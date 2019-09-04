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
struct ks_net {int promiscuous; scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS_RXCR1 ; 
 int RXCR1_FILTER_MASK ; 
 int RXCR1_RXAE ; 
 int RXCR1_RXINVF ; 
 int RXCR1_RXPAFMA ; 
 int ks_rdreg16 (struct ks_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_start_rx (struct ks_net*) ; 
 int /*<<< orphan*/  ks_stop_rx (struct ks_net*) ; 
 int /*<<< orphan*/  ks_wrreg16 (struct ks_net*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ks_set_promis(struct ks_net *ks, u16 promiscuous_mode)
{
	u16		cntl;
	ks->promiscuous = promiscuous_mode;
	ks_stop_rx(ks);  /* Stop receiving for reconfiguration */
	cntl = ks_rdreg16(ks, KS_RXCR1);

	cntl &= ~RXCR1_FILTER_MASK;
	if (promiscuous_mode)
		/* Enable Promiscuous mode */
		cntl |= RXCR1_RXAE | RXCR1_RXINVF;
	else
		/* Disable Promiscuous mode (default normal mode) */
		cntl |= RXCR1_RXPAFMA;

	ks_wrreg16(ks, KS_RXCR1, cntl);

	if (ks->enabled)
		ks_start_rx(ks);

}