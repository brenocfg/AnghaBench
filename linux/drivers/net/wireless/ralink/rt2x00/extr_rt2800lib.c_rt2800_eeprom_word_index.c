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
struct rt2x00_dev {TYPE_1__* hw; } ;
typedef  enum rt2800_eeprom_word { ____Placeholder_rt2800_eeprom_word } rt2800_eeprom_word ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int const EEPROM_CHIP_ID ; 
 int const EEPROM_WORD_COUNT ; 
 int /*<<< orphan*/  RT3593 ; 
 int /*<<< orphan*/  RT3883 ; 
 scalar_t__ WARN_ONCE (int,char*,int /*<<< orphan*/ ,int const) ; 
 unsigned int* rt2800_eeprom_map ; 
 unsigned int* rt2800_eeprom_map_ext ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int rt2800_eeprom_word_index(struct rt2x00_dev *rt2x00dev,
					     const enum rt2800_eeprom_word word)
{
	const unsigned int *map;
	unsigned int index;

	if (WARN_ONCE(word >= EEPROM_WORD_COUNT,
		      "%s: invalid EEPROM word %d\n",
		      wiphy_name(rt2x00dev->hw->wiphy), word))
		return 0;

	if (rt2x00_rt(rt2x00dev, RT3593) ||
	    rt2x00_rt(rt2x00dev, RT3883))
		map = rt2800_eeprom_map_ext;
	else
		map = rt2800_eeprom_map;

	index = map[word];

	/* Index 0 is valid only for EEPROM_CHIP_ID.
	 * Otherwise it means that the offset of the
	 * given word is not initialized in the map,
	 * or that the field is not usable on the
	 * actual chipset.
	 */
	WARN_ONCE(word != EEPROM_CHIP_ID && index == 0,
		  "%s: invalid access of EEPROM word %d\n",
		  wiphy_name(rt2x00dev->hw->wiphy), word);

	return index;
}