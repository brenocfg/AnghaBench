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
typedef  int /*<<< orphan*/  u16 ;
struct rt2x00_dev {int dummy; } ;
typedef  enum rt2800_eeprom_word { ____Placeholder_rt2800_eeprom_word } rt2800_eeprom_word ;

/* Variables and functions */
 unsigned int rt2800_eeprom_word_index (struct rt2x00_dev*,int const) ; 
 int /*<<< orphan*/  rt2x00_eeprom_write (struct rt2x00_dev*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2800_eeprom_write(struct rt2x00_dev *rt2x00dev,
				const enum rt2800_eeprom_word word, u16 data)
{
	unsigned int index;

	index = rt2800_eeprom_word_index(rt2x00dev, word);
	rt2x00_eeprom_write(rt2x00dev, index, data);
}