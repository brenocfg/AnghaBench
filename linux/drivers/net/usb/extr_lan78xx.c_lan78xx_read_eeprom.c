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
typedef  int u32 ;
struct lan78xx_net {int dummy; } ;

/* Variables and functions */
 scalar_t__ EEPROM_INDICATOR ; 
 int EINVAL ; 
 int lan78xx_read_raw_eeprom (struct lan78xx_net*,int,int,scalar_t__*) ; 

__attribute__((used)) static int lan78xx_read_eeprom(struct lan78xx_net *dev, u32 offset,
			       u32 length, u8 *data)
{
	u8 sig;
	int ret;

	ret = lan78xx_read_raw_eeprom(dev, 0, 1, &sig);
	if ((ret == 0) && (sig == EEPROM_INDICATOR))
		ret = lan78xx_read_raw_eeprom(dev, offset, length, data);
	else
		ret = -EINVAL;

	return ret;
}