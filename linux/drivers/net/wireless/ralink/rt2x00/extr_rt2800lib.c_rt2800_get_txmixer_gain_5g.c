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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_TXMIXER_GAIN_A ; 
 int /*<<< orphan*/  EEPROM_TXMIXER_GAIN_A_VAL ; 
 int /*<<< orphan*/  RT3593 ; 
 int /*<<< orphan*/  RT3883 ; 
 int rt2800_eeprom_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_get_field16 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 rt2800_get_txmixer_gain_5g(struct rt2x00_dev *rt2x00dev)
{
	u16 word;

	if (rt2x00_rt(rt2x00dev, RT3593) ||
	    rt2x00_rt(rt2x00dev, RT3883))
		return 0;

	word = rt2800_eeprom_read(rt2x00dev, EEPROM_TXMIXER_GAIN_A);
	if ((word & 0x00ff) != 0x00ff)
		return rt2x00_get_field16(word, EEPROM_TXMIXER_GAIN_A_VAL);

	return 0;
}