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
struct ucc_hdlc_private {unsigned short encoding; unsigned short parity; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct ucc_hdlc_private* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned short ENCODING_NRZ ; 
 unsigned short ENCODING_NRZI ; 
 unsigned short PARITY_CRC16_PR0_CCITT ; 
 unsigned short PARITY_CRC16_PR1_CCITT ; 
 unsigned short PARITY_CRC32_PR1_CCITT ; 
 unsigned short PARITY_NONE ; 
 TYPE_1__* dev_to_hdlc (struct net_device*) ; 

__attribute__((used)) static int ucc_hdlc_attach(struct net_device *dev, unsigned short encoding,
			   unsigned short parity)
{
	struct ucc_hdlc_private *priv = dev_to_hdlc(dev)->priv;

	if (encoding != ENCODING_NRZ &&
	    encoding != ENCODING_NRZI)
		return -EINVAL;

	if (parity != PARITY_NONE &&
	    parity != PARITY_CRC32_PR1_CCITT &&
	    parity != PARITY_CRC16_PR0_CCITT &&
	    parity != PARITY_CRC16_PR1_CCITT)
		return -EINVAL;

	priv->encoding = encoding;
	priv->parity = parity;

	return 0;
}