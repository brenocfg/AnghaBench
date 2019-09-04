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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct tda9950_priv {int addresses; int /*<<< orphan*/  client; } ;
struct cec_adapter {struct tda9950_priv* priv; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 scalar_t__ CEC_LOG_ADDR_INVALID ; 
 int /*<<< orphan*/  REG_ACKH ; 
 int tda9950_write_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static int tda9950_cec_adap_log_addr(struct cec_adapter *adap, u8 addr)
{
	struct tda9950_priv *priv = adap->priv;
	u16 addresses;
	u8 buf[2];

	if (addr == CEC_LOG_ADDR_INVALID)
		addresses = priv->addresses = 0;
	else
		addresses = priv->addresses |= BIT(addr);

	/* TDA9950 doesn't want address 15 set */
	addresses &= 0x7fff;
	buf[0] = addresses >> 8;
	buf[1] = addresses;

	return tda9950_write_range(priv->client, REG_ACKH, buf, 2);
}