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
typedef  int u8 ;
struct cc2520_private {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CC2520_TXPOWER ; 
 int EINVAL ; 
 int cc2520_write_register (struct cc2520_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int cc2520_cc2591_set_tx_power(struct cc2520_private *priv,
					     s32 mbm)
{
	u8 power;

	switch (mbm) {
	case 1700:
		power = 0xF9;
		break;
	case 1600:
		power = 0xF0;
		break;
	case 1400:
		power = 0xA0;
		break;
	case 1100:
		power = 0x2C;
		break;
	case -100:
		power = 0x03;
		break;
	case -800:
		power = 0x01;
		break;
	default:
		return -EINVAL;
	}

	return cc2520_write_register(priv, CC2520_TXPOWER, power);
}