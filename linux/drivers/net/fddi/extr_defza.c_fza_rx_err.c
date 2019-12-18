#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_crc_errors; } ;
struct fza_private {TYPE_2__ stats; TYPE_1__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  control_a; } ;

/* Variables and functions */
 int const FDDI_FC_K_CLASS_ASYNC ; 
 int const FDDI_FC_K_CLASS_MASK ; 
#define  FDDI_FC_K_FORMAT_LLC 134 
#define  FDDI_FC_K_FORMAT_MANAGEMENT 133 
 int const FDDI_FC_K_FORMAT_MASK ; 
 int /*<<< orphan*/  FZA_CONTROL_A_HALT ; 
 int const FZA_RING_PBC_MASK ; 
 int const FZA_RING_RX_BAD ; 
 int const FZA_RING_RX_CRC ; 
 int const FZA_RING_RX_DA_CAM ; 
 int const FZA_RING_RX_DA_MASK ; 
 int const FZA_RING_RX_FSB_ERR ; 
 int const FZA_RING_RX_FSC_MASK ; 
#define  FZA_RING_RX_RRR_ABORT 132 
#define  FZA_RING_RX_RRR_DADDR 131 
#define  FZA_RING_RX_RRR_LENGTH 130 
 int const FZA_RING_RX_RRR_MASK ; 
#define  FZA_RING_RX_RRR_OK 129 
#define  FZA_RING_RX_RRR_SADDR 128 
 int const FZA_RING_RX_SA_ALIAS ; 
 int const FZA_RING_RX_SA_CAM ; 
 int const FZA_RING_RX_SA_MASK ; 
 int /*<<< orphan*/  readw_o (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writew_o (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int fza_rx_err(struct fza_private *fp,
			     const u32 rmc, const u8 fc)
{
	int len, min_len, max_len;

	len = rmc & FZA_RING_PBC_MASK;

	if (unlikely((rmc & FZA_RING_RX_BAD) != 0)) {
		fp->stats.rx_errors++;

		/* Check special status codes. */
		if ((rmc & (FZA_RING_RX_CRC | FZA_RING_RX_RRR_MASK |
			    FZA_RING_RX_DA_MASK | FZA_RING_RX_SA_MASK)) ==
		     (FZA_RING_RX_CRC | FZA_RING_RX_RRR_DADDR |
		      FZA_RING_RX_DA_CAM | FZA_RING_RX_SA_ALIAS)) {
			if (len >= 8190)
				fp->stats.rx_length_errors++;
			return 1;
		}
		if ((rmc & (FZA_RING_RX_CRC | FZA_RING_RX_RRR_MASK |
			    FZA_RING_RX_DA_MASK | FZA_RING_RX_SA_MASK)) ==
		     (FZA_RING_RX_CRC | FZA_RING_RX_RRR_DADDR |
		      FZA_RING_RX_DA_CAM | FZA_RING_RX_SA_CAM)) {
			/* Halt the interface to trigger a reset. */
			writew_o(FZA_CONTROL_A_HALT, &fp->regs->control_a);
			readw_o(&fp->regs->control_a);	/* Synchronize. */
			return 1;
		}

		/* Check the MAC status. */
		switch (rmc & FZA_RING_RX_RRR_MASK) {
		case FZA_RING_RX_RRR_OK:
			if ((rmc & FZA_RING_RX_CRC) != 0)
				fp->stats.rx_crc_errors++;
			else if ((rmc & FZA_RING_RX_FSC_MASK) == 0 ||
				 (rmc & FZA_RING_RX_FSB_ERR) != 0)
				fp->stats.rx_frame_errors++;
			return 1;
		case FZA_RING_RX_RRR_SADDR:
		case FZA_RING_RX_RRR_DADDR:
		case FZA_RING_RX_RRR_ABORT:
			/* Halt the interface to trigger a reset. */
			writew_o(FZA_CONTROL_A_HALT, &fp->regs->control_a);
			readw_o(&fp->regs->control_a);	/* Synchronize. */
			return 1;
		case FZA_RING_RX_RRR_LENGTH:
			fp->stats.rx_frame_errors++;
			return 1;
		default:
			return 1;
		}
	}

	/* Packet received successfully; validate the length. */
	switch (fc & FDDI_FC_K_FORMAT_MASK) {
	case FDDI_FC_K_FORMAT_MANAGEMENT:
		if ((fc & FDDI_FC_K_CLASS_MASK) == FDDI_FC_K_CLASS_ASYNC)
			min_len = 37;
		else
			min_len = 17;
		break;
	case FDDI_FC_K_FORMAT_LLC:
		min_len = 20;
		break;
	default:
		min_len = 17;
		break;
	}
	max_len = 4495;
	if (len < min_len || len > max_len) {
		fp->stats.rx_errors++;
		fp->stats.rx_length_errors++;
		return 1;
	}

	return 0;
}