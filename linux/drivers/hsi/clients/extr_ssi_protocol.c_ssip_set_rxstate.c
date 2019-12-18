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
struct ssi_protocol {unsigned int recv_state; int /*<<< orphan*/  rx_wd; int /*<<< orphan*/  keep_alive; int /*<<< orphan*/  tx_usecnt; int /*<<< orphan*/  send_state; } ;

/* Variables and functions */
#define  RECEIVING 130 
#define  RECV_IDLE 129 
#define  RECV_READY 128 
 int /*<<< orphan*/  SEND_IDLE ; 
 int /*<<< orphan*/  SSIP_KATOUT ; 
 int /*<<< orphan*/  SSIP_WDTOUT ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ssip_set_rxstate(struct ssi_protocol *ssi, unsigned int state)
{
	ssi->recv_state = state;
	switch (state) {
	case RECV_IDLE:
		del_timer(&ssi->rx_wd);
		if (ssi->send_state == SEND_IDLE)
			del_timer(&ssi->keep_alive);
		break;
	case RECV_READY:
		/* CMT speech workaround */
		if (atomic_read(&ssi->tx_usecnt))
			break;
		/* Else, fall through */
	case RECEIVING:
		mod_timer(&ssi->keep_alive, jiffies +
						msecs_to_jiffies(SSIP_KATOUT));
		mod_timer(&ssi->rx_wd, jiffies + msecs_to_jiffies(SSIP_WDTOUT));
		break;
	default:
		break;
	}
}