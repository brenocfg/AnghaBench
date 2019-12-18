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
struct soc_pcmcia_socket {int dummy; } ;
struct pcmcia_state {int vs_3v; scalar_t__ vs_Xv; } ;

/* Variables and functions */
 long PCMCIA_VS1 ; 
 long PCMCIA_VS2 ; 
 long simpad_get_cs3_ro () ; 

__attribute__((used)) static void
simpad_pcmcia_socket_state(struct soc_pcmcia_socket *skt,
			   struct pcmcia_state *state)
{
	long cs3reg = simpad_get_cs3_ro();

	/* bvd1 might be cs3reg & PCMCIA_BVD1 */
	/* bvd2 might be cs3reg & PCMCIA_BVD2 */

	if ((cs3reg & (PCMCIA_VS1|PCMCIA_VS2)) ==
			(PCMCIA_VS1|PCMCIA_VS2)) {
		state->vs_3v=0;
		state->vs_Xv=0;
	} else {
		state->vs_3v=1;
		state->vs_Xv=0;
	}
}