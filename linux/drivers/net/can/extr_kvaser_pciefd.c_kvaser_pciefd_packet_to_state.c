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
struct kvaser_pciefd_rx_packet {int* header; } ;
struct can_berr_counter {int txerr; int rxerr; } ;
typedef  enum can_state { ____Placeholder_can_state } can_state ;

/* Variables and functions */
 int CAN_STATE_BUS_OFF ; 
 int CAN_STATE_ERROR_ACTIVE ; 
 int CAN_STATE_ERROR_PASSIVE ; 
 int CAN_STATE_ERROR_WARNING ; 
 int KVASER_PCIEFD_SPACK_BOFF ; 
 int KVASER_PCIEFD_SPACK_EPLR ; 
 int KVASER_PCIEFD_SPACK_EWLR ; 
 int KVASER_PCIEFD_SPACK_IRM ; 

__attribute__((used)) static void kvaser_pciefd_packet_to_state(struct kvaser_pciefd_rx_packet *p,
					  struct can_berr_counter *bec,
					  enum can_state *new_state,
					  enum can_state *tx_state,
					  enum can_state *rx_state)
{
	if (p->header[0] & KVASER_PCIEFD_SPACK_BOFF ||
	    p->header[0] & KVASER_PCIEFD_SPACK_IRM)
		*new_state = CAN_STATE_BUS_OFF;
	else if (bec->txerr >= 255 ||  bec->rxerr >= 255)
		*new_state = CAN_STATE_BUS_OFF;
	else if (p->header[1] & KVASER_PCIEFD_SPACK_EPLR)
		*new_state = CAN_STATE_ERROR_PASSIVE;
	else if (bec->txerr >= 128 || bec->rxerr >= 128)
		*new_state = CAN_STATE_ERROR_PASSIVE;
	else if (p->header[1] & KVASER_PCIEFD_SPACK_EWLR)
		*new_state = CAN_STATE_ERROR_WARNING;
	else if (bec->txerr >= 96 || bec->rxerr >= 96)
		*new_state = CAN_STATE_ERROR_WARNING;
	else
		*new_state = CAN_STATE_ERROR_ACTIVE;

	*tx_state = bec->txerr >= bec->rxerr ? *new_state : 0;
	*rx_state = bec->txerr <= bec->rxerr ? *new_state : 0;
}