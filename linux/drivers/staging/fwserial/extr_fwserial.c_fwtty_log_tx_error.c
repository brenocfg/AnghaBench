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
struct fwtty_port {int dummy; } ;

/* Variables and functions */
#define  RCODE_ADDRESS_ERROR 132 
#define  RCODE_BUSY 131 
#define  RCODE_DATA_ERROR 130 
#define  RCODE_NO_ACK 129 
#define  RCODE_SEND_ERROR 128 
 int /*<<< orphan*/  fwtty_err_ratelimited (struct fwtty_port*,char*,...) ; 

__attribute__((used)) static void fwtty_log_tx_error(struct fwtty_port *port, int rcode)
{
	switch (rcode) {
	case RCODE_SEND_ERROR:
		fwtty_err_ratelimited(port, "card busy\n");
		break;
	case RCODE_ADDRESS_ERROR:
		fwtty_err_ratelimited(port, "bad unit addr or write length\n");
		break;
	case RCODE_DATA_ERROR:
		fwtty_err_ratelimited(port, "failed rx\n");
		break;
	case RCODE_NO_ACK:
		fwtty_err_ratelimited(port, "missing ack\n");
		break;
	case RCODE_BUSY:
		fwtty_err_ratelimited(port, "remote busy\n");
		break;
	default:
		fwtty_err_ratelimited(port, "failed tx: %d\n", rcode);
	}
}