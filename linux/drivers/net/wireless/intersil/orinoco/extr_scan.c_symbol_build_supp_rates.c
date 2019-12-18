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
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int WLAN_EID_SUPP_RATES ; 
 int le16_to_cpu (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int symbol_build_supp_rates(u8 *buf, const __le16 *rates)
{
	int i;
	u8 rate;

	buf[0] = WLAN_EID_SUPP_RATES;
	for (i = 0; i < 5; i++) {
		rate = le16_to_cpu(rates[i]);
		/* NULL terminated */
		if (rate == 0x0)
			break;
		buf[i + 2] = rate;
	}
	buf[1] = i;

	return i + 2;
}