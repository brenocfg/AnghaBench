#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct jsm_channel {int ch_cached_lsr; int ch_flags; TYPE_1__* ch_neo_uart; } ;
struct TYPE_2__ {int /*<<< orphan*/  lsr; } ;

/* Variables and functions */
 int CH_TX_FIFO_EMPTY ; 
 int CH_TX_FIFO_LWM ; 
 int UART_LSR_TEMT ; 
 int readb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 neo_get_uart_bytes_left(struct jsm_channel *ch)
{
	u8 left = 0;
	u8 lsr = readb(&ch->ch_neo_uart->lsr);

	/* We must cache the LSR as some of the bits get reset once read... */
	ch->ch_cached_lsr |= lsr;

	/* Determine whether the Transmitter is empty or not */
	if (!(lsr & UART_LSR_TEMT))
		left = 1;
	else {
		ch->ch_flags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);
		left = 0;
	}

	return left;
}