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
struct mvneta_rx_desc {int status; int /*<<< orphan*/  data_size; } ;
struct mvneta_port {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MVNETA_RXD_ERR_CODE_MASK ; 
#define  MVNETA_RXD_ERR_CRC 131 
#define  MVNETA_RXD_ERR_LEN 130 
#define  MVNETA_RXD_ERR_OVERRUN 129 
#define  MVNETA_RXD_ERR_RESOURCE 128 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvneta_rx_error(struct mvneta_port *pp,
			    struct mvneta_rx_desc *rx_desc)
{
	u32 status = rx_desc->status;

	switch (status & MVNETA_RXD_ERR_CODE_MASK) {
	case MVNETA_RXD_ERR_CRC:
		netdev_err(pp->dev, "bad rx status %08x (crc error), size=%d\n",
			   status, rx_desc->data_size);
		break;
	case MVNETA_RXD_ERR_OVERRUN:
		netdev_err(pp->dev, "bad rx status %08x (overrun error), size=%d\n",
			   status, rx_desc->data_size);
		break;
	case MVNETA_RXD_ERR_LEN:
		netdev_err(pp->dev, "bad rx status %08x (max frame length error), size=%d\n",
			   status, rx_desc->data_size);
		break;
	case MVNETA_RXD_ERR_RESOURCE:
		netdev_err(pp->dev, "bad rx status %08x (resource error), size=%d\n",
			   status, rx_desc->data_size);
		break;
	}
}