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
typedef  int uint ;
struct fec_enet_private {int work_rx; int work_tx; } ;

/* Variables and functions */
 int FEC_ENET_RXF_0 ; 
 int FEC_ENET_RXF_1 ; 
 int FEC_ENET_RXF_2 ; 
 int FEC_ENET_TXF_0 ; 
 int FEC_ENET_TXF_1 ; 
 int FEC_ENET_TXF_2 ; 

__attribute__((used)) static bool
fec_enet_collect_events(struct fec_enet_private *fep, uint int_events)
{
	if (int_events == 0)
		return false;

	if (int_events & FEC_ENET_RXF_0)
		fep->work_rx |= (1 << 2);
	if (int_events & FEC_ENET_RXF_1)
		fep->work_rx |= (1 << 0);
	if (int_events & FEC_ENET_RXF_2)
		fep->work_rx |= (1 << 1);

	if (int_events & FEC_ENET_TXF_0)
		fep->work_tx |= (1 << 2);
	if (int_events & FEC_ENET_TXF_1)
		fep->work_tx |= (1 << 0);
	if (int_events & FEC_ENET_TXF_2)
		fep->work_tx |= (1 << 1);

	return true;
}