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
 scalar_t__ RX8571_USER_RAM ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,scalar_t__,void*,size_t) ; 

__attribute__((used)) static int rx8571_nvram_read(void *priv, unsigned int offset, void *val,
			     size_t bytes)
{
	struct rx8581 *rx8581 = priv;

	return regmap_bulk_read(rx8581->regmap, RX8571_USER_RAM + offset,
				val, bytes);
}