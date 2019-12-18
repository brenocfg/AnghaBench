#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct soc_pcmcia_socket {int nr; struct max1600* driver_data; } ;
struct pcmcia_state {int /*<<< orphan*/  vs_Xv; int /*<<< orphan*/  vs_3v; } ;
struct max1600 {int dummy; } ;
struct TYPE_4__ {int Vcc; int Vpp; } ;
typedef  TYPE_1__ socket_state_t ;

/* Variables and functions */
 int max1600_configure (struct max1600*,int,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int sa1111_pcmcia_configure_socket (struct soc_pcmcia_socket*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  sa1111_pcmcia_socket_state (struct soc_pcmcia_socket*,struct pcmcia_state*) ; 

__attribute__((used)) static int
lubbock_pcmcia_configure_socket(struct soc_pcmcia_socket *skt,
				const socket_state_t *state)
{
	struct max1600 *m = skt->driver_data;
	int ret = 0;

	/* Lubbock uses the Maxim MAX1602, with the following connections:
	 *
	 * Socket 0 (PCMCIA):
	 *	MAX1602	Lubbock		Register
	 *	Pin	Signal
	 *	-----	-------		----------------------
	 *	A0VPP	S0_PWR0		SA-1111 GPIO A<0>
	 *	A1VPP	S0_PWR1		SA-1111 GPIO A<1>
	 *	A0VCC	S0_PWR2		SA-1111 GPIO A<2>
	 *	A1VCC	S0_PWR3		SA-1111 GPIO A<3>
	 *	VX	VCC
	 *	VY	+3.3V
	 *	12IN	+12V
	 *	CODE	+3.3V		Cirrus  Code, CODE = High (VY)
	 *
	 * Socket 1 (CF):
	 *	MAX1602	Lubbock		Register
	 *	Pin	Signal
	 *	-----	-------		----------------------
	 *	A0VPP	GND		VPP is not connected
	 *	A1VPP	GND		VPP is not connected
	 *	A0VCC	S1_PWR0		MISC_WR<14>
	 *	A1VCC	S1_PWR1		MISC_WR<15>
	 *	VX	VCC
	 *	VY	+3.3V
	 *	12IN	GND		VPP is not connected
	 *	CODE	+3.3V		Cirrus  Code, CODE = High (VY)
	 *
	 */

 again:
	switch (skt->nr) {
	case 0:
	case 1:
		break;

	default:
		ret = -1;
	}

	if (ret == 0)
		ret = sa1111_pcmcia_configure_socket(skt, state);
	if (ret == 0)
		ret = max1600_configure(m, state->Vcc, state->Vpp);

#if 1
	if (ret == 0 && state->Vcc == 33) {
		struct pcmcia_state new_state;

		/*
		 * HACK ALERT:
		 * We can't sense the voltage properly on Lubbock before
		 * actually applying some power to the socket (catch 22).
		 * Resense the socket Voltage Sense pins after applying
		 * socket power.
		 *
		 * Note: It takes about 2.5ms for the MAX1602 VCC output
		 * to rise.
		 */
		mdelay(3);

		sa1111_pcmcia_socket_state(skt, &new_state);

		if (!new_state.vs_3v && !new_state.vs_Xv) {
			/*
			 * Switch to 5V,  Configure socket with 5V voltage
			 */
			max1600_configure(m, 0, 0);

			/*
			 * It takes about 100ms to turn off Vcc.
			 */
			mdelay(100);

			/*
			 * We need to hack around the const qualifier as
			 * well to keep this ugly workaround localized and
			 * not force it to the rest of the code. Barf bags
			 * available in the seat pocket in front of you!
			 */
			((socket_state_t *)state)->Vcc = 50;
			((socket_state_t *)state)->Vpp = 50;
			goto again;
		}
	}
#endif

	return ret;
}