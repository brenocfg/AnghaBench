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
struct zatm_dev {int dummy; } ;

/* Variables and functions */
 unsigned long ZEPROM_CS ; 
 unsigned long ZEPROM_DI ; 
 unsigned long ZEPROM_SK ; 
 int /*<<< orphan*/  eprom_set (struct zatm_dev*,unsigned long,unsigned short) ; 

__attribute__((used)) static void eprom_put_bits(struct zatm_dev *zatm_dev, unsigned long data,
			   int bits, unsigned short cmd)
{
	unsigned long value;
	int i;

	for (i = bits-1; i >= 0; i--) {
		value = ZEPROM_CS | (((data >> i) & 1) ? ZEPROM_DI : 0);
		eprom_set(zatm_dev,value,cmd);
		eprom_set(zatm_dev,value | ZEPROM_SK,cmd);
		eprom_set(zatm_dev,value,cmd);
	}
}