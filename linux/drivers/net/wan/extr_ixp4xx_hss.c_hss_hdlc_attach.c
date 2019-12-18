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
struct port {int /*<<< orphan*/  hdlc_cfg; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned short ENCODING_NRZ ; 
#define  PARITY_CRC16_PR1_CCITT 129 
#define  PARITY_CRC32_PR1_CCITT 128 
 int /*<<< orphan*/  PKT_HDLC_CRC_32 ; 
 struct port* dev_to_port (struct net_device*) ; 

__attribute__((used)) static int hss_hdlc_attach(struct net_device *dev, unsigned short encoding,
			   unsigned short parity)
{
	struct port *port = dev_to_port(dev);

	if (encoding != ENCODING_NRZ)
		return -EINVAL;

	switch(parity) {
	case PARITY_CRC16_PR1_CCITT:
		port->hdlc_cfg = 0;
		return 0;

	case PARITY_CRC32_PR1_CCITT:
		port->hdlc_cfg = PKT_HDLC_CRC_32;
		return 0;

	default:
		return -EINVAL;
	}
}