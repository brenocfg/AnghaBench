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
struct net_device {int dummy; } ;
struct board_info {int ip_summed; } ;

/* Variables and functions */
 int CHECKSUM_NONE ; 
 int /*<<< orphan*/  DM9000_TCCR ; 
 int /*<<< orphan*/  DM9000_TCR ; 
 int /*<<< orphan*/  DM9000_TXPLH ; 
 int /*<<< orphan*/  DM9000_TXPLL ; 
 int TCCR_IP ; 
 int TCCR_TCP ; 
 int TCCR_UDP ; 
 int TCR_TXREQ ; 
 int /*<<< orphan*/  iow (struct board_info*,int /*<<< orphan*/ ,int) ; 
 struct board_info* to_dm9000_board (struct net_device*) ; 

__attribute__((used)) static void dm9000_send_packet(struct net_device *dev,
			       int ip_summed,
			       u16 pkt_len)
{
	struct board_info *dm = to_dm9000_board(dev);

	/* The DM9000 is not smart enough to leave fragmented packets alone. */
	if (dm->ip_summed != ip_summed) {
		if (ip_summed == CHECKSUM_NONE)
			iow(dm, DM9000_TCCR, 0);
		else
			iow(dm, DM9000_TCCR, TCCR_IP | TCCR_UDP | TCCR_TCP);
		dm->ip_summed = ip_summed;
	}

	/* Set TX length to DM9000 */
	iow(dm, DM9000_TXPLL, pkt_len);
	iow(dm, DM9000_TXPLH, pkt_len >> 8);

	/* Issue TX polling command */
	iow(dm, DM9000_TCR, TCR_TXREQ);	/* Cleared after TX complete */
}