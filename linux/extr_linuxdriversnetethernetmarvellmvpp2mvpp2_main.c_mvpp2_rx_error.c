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
typedef  int u32 ;
struct mvpp2_rx_desc {int dummy; } ;
struct mvpp2_port {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MVPP2_RXD_ERR_CODE_MASK ; 
#define  MVPP2_RXD_ERR_CRC 130 
#define  MVPP2_RXD_ERR_OVERRUN 129 
#define  MVPP2_RXD_ERR_RESOURCE 128 
 size_t mvpp2_rxdesc_size_get (struct mvpp2_port*,struct mvpp2_rx_desc*) ; 
 int mvpp2_rxdesc_status_get (struct mvpp2_port*,struct mvpp2_rx_desc*) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int,char*,size_t) ; 

__attribute__((used)) static void mvpp2_rx_error(struct mvpp2_port *port,
			   struct mvpp2_rx_desc *rx_desc)
{
	u32 status = mvpp2_rxdesc_status_get(port, rx_desc);
	size_t sz = mvpp2_rxdesc_size_get(port, rx_desc);
	char *err_str = NULL;

	switch (status & MVPP2_RXD_ERR_CODE_MASK) {
	case MVPP2_RXD_ERR_CRC:
		err_str = "crc";
		break;
	case MVPP2_RXD_ERR_OVERRUN:
		err_str = "overrun";
		break;
	case MVPP2_RXD_ERR_RESOURCE:
		err_str = "resource";
		break;
	}
	if (err_str && net_ratelimit())
		netdev_err(port->dev,
			   "bad rx status %08x (%s error), size=%zu\n",
			   status, err_str, sz);
}