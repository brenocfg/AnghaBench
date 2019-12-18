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
struct port {int /*<<< orphan*/  id; } ;
struct msg {int data32; scalar_t__ index; int /*<<< orphan*/  hss_port; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 scalar_t__ HSS_CONFIG_RX_LUT ; 
 scalar_t__ HSS_CONFIG_TX_LUT ; 
 int MAX_CHANNELS ; 
 int /*<<< orphan*/  PORT_CONFIG_WRITE ; 
 int TDMMAP_HDLC ; 
 int /*<<< orphan*/  hss_npe_send (struct port*,struct msg*,char*) ; 
 int /*<<< orphan*/  memset (struct msg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hss_config_set_lut(struct port *port)
{
	struct msg msg;
	int ch;

	memset(&msg, 0, sizeof(msg));
	msg.cmd = PORT_CONFIG_WRITE;
	msg.hss_port = port->id;

	for (ch = 0; ch < MAX_CHANNELS; ch++) {
		msg.data32 >>= 2;
		msg.data32 |= TDMMAP_HDLC << 30;

		if (ch % 16 == 15) {
			msg.index = HSS_CONFIG_TX_LUT + ((ch / 4) & ~3);
			hss_npe_send(port, &msg, "HSS_SET_TX_LUT");

			msg.index += HSS_CONFIG_RX_LUT - HSS_CONFIG_TX_LUT;
			hss_npe_send(port, &msg, "HSS_SET_RX_LUT");
		}
	}
}