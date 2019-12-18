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
struct rx8581 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX8581_REG_RAM ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int rx85x1_nvram_read(void *priv, unsigned int offset, void *val,
			     size_t bytes)
{
	struct rx8581 *rx8581 = priv;
	unsigned int tmp_val;
	int ret;

	ret = regmap_read(rx8581->regmap, RX8581_REG_RAM, &tmp_val);
	(*(unsigned char *)val) = (unsigned char) tmp_val;

	return ret;
}