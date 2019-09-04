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
struct pxa168_eth_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_CAUSE ; 
 int /*<<< orphan*/  INT_MASK ; 
 int /*<<< orphan*/  INT_W_CLEAR ; 
 int PCR_HS ; 
 int /*<<< orphan*/  PORT_CONFIG ; 
 int SDCR_BLMR ; 
 int SDCR_BLMT ; 
 int SDCR_BSZ8 ; 
 int SDCR_RC_MAX_RETRANS ; 
 int SDCR_RIFB ; 
 int /*<<< orphan*/  SDMA_CONFIG ; 
 int /*<<< orphan*/  abort_dma (struct pxa168_eth_private*) ; 
 int init_hash_table (struct pxa168_eth_private*) ; 
 int /*<<< orphan*/  set_port_config_ext (struct pxa168_eth_private*) ; 
 int /*<<< orphan*/  wrl (struct pxa168_eth_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pxa168_init_hw(struct pxa168_eth_private *pep)
{
	int err = 0;

	/* Disable interrupts */
	wrl(pep, INT_MASK, 0);
	wrl(pep, INT_CAUSE, 0);
	/* Write to ICR to clear interrupts. */
	wrl(pep, INT_W_CLEAR, 0);
	/* Abort any transmit and receive operations and put DMA
	 * in idle state.
	 */
	abort_dma(pep);
	/* Initialize address hash table */
	err = init_hash_table(pep);
	if (err)
		return err;
	/* SDMA configuration */
	wrl(pep, SDMA_CONFIG, SDCR_BSZ8 |	/* Burst size = 32 bytes */
	    SDCR_RIFB |				/* Rx interrupt on frame */
	    SDCR_BLMT |				/* Little endian transmit */
	    SDCR_BLMR |				/* Little endian receive */
	    SDCR_RC_MAX_RETRANS);		/* Max retransmit count */
	/* Port Configuration */
	wrl(pep, PORT_CONFIG, PCR_HS);		/* Hash size is 1/2kb */
	set_port_config_ext(pep);

	return err;
}