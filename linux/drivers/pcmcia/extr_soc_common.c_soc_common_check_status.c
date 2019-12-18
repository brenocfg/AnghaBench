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
struct TYPE_2__ {unsigned int csc_mask; } ;
struct soc_pcmcia_socket {unsigned int status; int /*<<< orphan*/  socket; TYPE_1__ cs_state; } ;

/* Variables and functions */
 unsigned int SS_BATDEAD ; 
 unsigned int SS_BATWARN ; 
 unsigned int SS_DETECT ; 
 unsigned int SS_READY ; 
 unsigned int SS_STSCHG ; 
 int /*<<< orphan*/  debug (struct soc_pcmcia_socket*,int,char*,...) ; 
 int /*<<< orphan*/  pcmcia_parse_events (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int soc_common_pcmcia_skt_state (struct soc_pcmcia_socket*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  status_lock ; 

__attribute__((used)) static void soc_common_check_status(struct soc_pcmcia_socket *skt)
{
	unsigned int events;

	debug(skt, 4, "entering PCMCIA monitoring thread\n");

	do {
		unsigned int status;
		unsigned long flags;

		status = soc_common_pcmcia_skt_state(skt);

		spin_lock_irqsave(&status_lock, flags);
		events = (status ^ skt->status) & skt->cs_state.csc_mask;
		skt->status = status;
		spin_unlock_irqrestore(&status_lock, flags);

		debug(skt, 4, "events: %s%s%s%s%s%s\n",
			events == 0         ? "<NONE>"   : "",
			events & SS_DETECT  ? "DETECT "  : "",
			events & SS_READY   ? "READY "   : "",
			events & SS_BATDEAD ? "BATDEAD " : "",
			events & SS_BATWARN ? "BATWARN " : "",
			events & SS_STSCHG  ? "STSCHG "  : "");

		if (events)
			pcmcia_parse_events(&skt->socket, events);
	} while (events);
}