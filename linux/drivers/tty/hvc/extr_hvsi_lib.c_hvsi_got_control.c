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
struct hvsi_priv {scalar_t__ inbuf; } ;
struct hvsi_control {int /*<<< orphan*/  word; int /*<<< orphan*/  verb; } ;

/* Variables and functions */
 int HVSI_TSCD ; 
#define  VSV_CLOSE_PROTOCOL 129 
#define  VSV_MODEM_CTL_UPDATE 128 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hvsi_cd_change (struct hvsi_priv*,int) ; 
 int /*<<< orphan*/  hvsi_start_handshake (struct hvsi_priv*) ; 

__attribute__((used)) static void hvsi_got_control(struct hvsi_priv *pv)
{
	struct hvsi_control *pkt = (struct hvsi_control *)pv->inbuf;

	switch (be16_to_cpu(pkt->verb)) {
	case VSV_CLOSE_PROTOCOL:
		/* We restart the handshaking */
		hvsi_start_handshake(pv);
		break;
	case VSV_MODEM_CTL_UPDATE:
		/* Transition of carrier detect */
		hvsi_cd_change(pv, be32_to_cpu(pkt->word) & HVSI_TSCD);
		break;
	}
}