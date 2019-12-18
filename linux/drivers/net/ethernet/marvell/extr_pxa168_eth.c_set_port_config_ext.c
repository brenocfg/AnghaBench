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
struct pxa168_eth_private {int skb_size; } ;

/* Variables and functions */
 int PCXR_2BSM ; 
 int PCXR_AN_DUPLEX_DIS ; 
 int PCXR_AN_FLOWCTL_DIS ; 
 int PCXR_AN_SPEED_DIS ; 
 int PCXR_DSCP_EN ; 
 int PCXR_FLP ; 
 int PCXR_MFL_1518 ; 
 int PCXR_MFL_1536 ; 
 int PCXR_MFL_2048 ; 
 int PCXR_MFL_64K ; 
 int PCXR_TX_HIGH_PRI ; 
 int /*<<< orphan*/  PORT_CONFIG_EXT ; 
 int /*<<< orphan*/  pxa168_eth_recalc_skb_size (struct pxa168_eth_private*) ; 
 int /*<<< orphan*/  wrl (struct pxa168_eth_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_port_config_ext(struct pxa168_eth_private *pep)
{
	int skb_size;

	pxa168_eth_recalc_skb_size(pep);
	if  (pep->skb_size <= 1518)
		skb_size = PCXR_MFL_1518;
	else if (pep->skb_size <= 1536)
		skb_size = PCXR_MFL_1536;
	else if (pep->skb_size <= 2048)
		skb_size = PCXR_MFL_2048;
	else
		skb_size = PCXR_MFL_64K;

	/* Extended Port Configuration */
	wrl(pep, PORT_CONFIG_EXT,
	    PCXR_AN_SPEED_DIS |		 /* Disable HW AN */
	    PCXR_AN_DUPLEX_DIS |
	    PCXR_AN_FLOWCTL_DIS |
	    PCXR_2BSM |			 /* Two byte prefix aligns IP hdr */
	    PCXR_DSCP_EN |		 /* Enable DSCP in IP */
	    skb_size | PCXR_FLP |	 /* do not force link pass */
	    PCXR_TX_HIGH_PRI);		 /* Transmit - high priority queue */

	return 0;
}