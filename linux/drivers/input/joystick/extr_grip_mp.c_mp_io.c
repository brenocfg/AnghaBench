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
typedef  int u8 ;
typedef  int u32 ;
struct gameport {int dummy; } ;

/* Variables and functions */
 int IO_GOT_PACKET ; 
 int IO_MODE_FAST ; 
 int IO_RESET ; 
 int IO_RETRY ; 
 int PACKET_FULL ; 
 int PACKET_IO_FAST ; 
 int PACKET_IO_SLOW ; 
 int PACKET_MP_DONE ; 
 int PACKET_MP_MORE ; 
 int bit_parity (int) ; 
 int gameport_read (struct gameport*) ; 
 int /*<<< orphan*/  gameport_trigger (struct gameport*) ; 
 int /*<<< orphan*/  poll_until (int,int,int,struct gameport*,int*) ; 

__attribute__((used)) static int mp_io(struct gameport* gameport, int sendflags, int sendcode, u32 *packet)
{
	u8  raw_data;            /* raw data from gameport */
	u8  data_mask;           /* packet data bits from raw_data */
	u32 pkt;                 /* packet temporary storage */
	int bits_per_read;       /* num packet bits per gameport read */
	int portvals = 0;        /* used for port value sanity check */
	int i;

	/* Gameport bits B0, B4, B5 should first be off, then B4 should come on. */

	*packet = 0;
	raw_data = gameport_read(gameport);
	if (raw_data & 1)
		return IO_RETRY;

	for (i = 0; i < 64; i++) {
		raw_data = gameport_read(gameport);
		portvals |= 1 << ((raw_data >> 4) & 3); /* Demux B4, B5 */
	}

	if (portvals == 1) {                            /* B4, B5 off */
		raw_data = gameport_read(gameport);
		portvals = raw_data & 0xf0;

		if (raw_data & 0x31)
			return IO_RESET;
		gameport_trigger(gameport);

		if (!poll_until(0x10, 0, 308, gameport, &raw_data))
			return IO_RESET;
	} else
		return IO_RETRY;

	/* Determine packet transfer mode and prepare for packet construction. */

	if (raw_data & 0x20) {                 /* 3 data bits/read */
		portvals |= raw_data >> 4;     /* Compare B4-B7 before & after trigger */

		if (portvals != 0xb)
			return 0;
		data_mask = 7;
		bits_per_read = 3;
		pkt = (PACKET_FULL | PACKET_IO_FAST) >> 28;
	} else {                                 /* 1 data bit/read */
		data_mask = 1;
		bits_per_read = 1;
		pkt = (PACKET_FULL | PACKET_IO_SLOW) >> 28;
	}

	/* Construct a packet.  Final data bits must be zero. */

	while (1) {
		if (!poll_until(0, 0x10, 77, gameport, &raw_data))
			return IO_RESET;
		raw_data = (raw_data >> 5) & data_mask;

		if (pkt & PACKET_FULL)
			break;
		pkt = (pkt << bits_per_read) | raw_data;

		if (!poll_until(0x10, 0, 77, gameport, &raw_data))
			return IO_RESET;
	}

	if (raw_data)
		return IO_RESET;

	/* If 3 bits/read used, drop from 30 bits to 28. */

	if (bits_per_read == 3) {
		pkt = (pkt & 0xffff0000) | ((pkt << 1) & 0xffff);
		pkt = (pkt >> 2) | 0xf0000000;
	}

	if (bit_parity(pkt) == 1)
		return IO_RESET;

	/* Acknowledge packet receipt */

	if (!poll_until(0x30, 0, 77, gameport, &raw_data))
		return IO_RESET;

	raw_data = gameport_read(gameport);

	if (raw_data & 1)
		return IO_RESET;

	gameport_trigger(gameport);

	if (!poll_until(0, 0x20, 77, gameport, &raw_data))
		return IO_RESET;

        /* Return if we just wanted the packet or multiport wants to send more */

	*packet = pkt;
	if ((sendflags == 0) || ((sendflags & IO_RETRY) && !(pkt & PACKET_MP_DONE)))
		return IO_GOT_PACKET;

	if (pkt & PACKET_MP_MORE)
		return IO_GOT_PACKET | IO_RETRY;

	/* Multiport is done sending packets and is ready to receive data */

	if (!poll_until(0x20, 0, 77, gameport, &raw_data))
		return IO_GOT_PACKET | IO_RESET;

	raw_data = gameport_read(gameport);
	if (raw_data & 1)
		return IO_GOT_PACKET | IO_RESET;

	/* Trigger gameport based on bits in sendcode */

	gameport_trigger(gameport);
	do {
		if (!poll_until(0x20, 0x10, 116, gameport, &raw_data))
			return IO_GOT_PACKET | IO_RESET;

		if (!poll_until(0x30, 0, 193, gameport, &raw_data))
			return IO_GOT_PACKET | IO_RESET;

		if (raw_data & 1)
			return IO_GOT_PACKET | IO_RESET;

		if (sendcode & 1)
			gameport_trigger(gameport);

		sendcode >>= 1;
	} while (sendcode);

	return IO_GOT_PACKET | IO_MODE_FAST;
}