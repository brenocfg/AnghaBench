#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char u8 ;
struct TYPE_4__ {char* override_addr; char id; int mac_override; TYPE_1__* ksz_switch; } ;
struct dev_info {TYPE_2__ hw; } ;
struct TYPE_3__ {char* other_addr; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int MAIN_PORT ; 
 int hex_to_bin (char) ; 

__attribute__((used)) static void get_mac_addr(struct dev_info *hw_priv, u8 *macaddr, int port)
{
	int i;
	int j;
	int got_num;
	int num;

	i = j = num = got_num = 0;
	while (j < ETH_ALEN) {
		if (macaddr[i]) {
			int digit;

			got_num = 1;
			digit = hex_to_bin(macaddr[i]);
			if (digit >= 0)
				num = num * 16 + digit;
			else if (':' == macaddr[i])
				got_num = 2;
			else
				break;
		} else if (got_num)
			got_num = 2;
		else
			break;
		if (2 == got_num) {
			if (MAIN_PORT == port) {
				hw_priv->hw.override_addr[j++] = (u8) num;
				hw_priv->hw.override_addr[5] +=
					hw_priv->hw.id;
			} else {
				hw_priv->hw.ksz_switch->other_addr[j++] =
					(u8) num;
				hw_priv->hw.ksz_switch->other_addr[5] +=
					hw_priv->hw.id;
			}
			num = got_num = 0;
		}
		i++;
	}
	if (ETH_ALEN == j) {
		if (MAIN_PORT == port)
			hw_priv->hw.mac_override = 1;
	}
}