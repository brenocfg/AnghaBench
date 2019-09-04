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
struct apds990x_chip {scalar_t__ prox_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  APDS990X_ENABLE ; 
 int APDS990X_EN_AEN ; 
 int APDS990X_EN_AIEN ; 
 int APDS990X_EN_PEN ; 
 int APDS990X_EN_PIEN ; 
 int APDS990X_EN_PON ; 
 int APDS990X_EN_WEN ; 
 int apds990x_write_byte (struct apds990x_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int apds990x_mode_on(struct apds990x_chip *chip)
{
	/* ALS is mandatory, proximity optional */
	u8 reg = APDS990X_EN_AIEN | APDS990X_EN_PON | APDS990X_EN_AEN |
		APDS990X_EN_WEN;

	if (chip->prox_en)
		reg |= APDS990X_EN_PIEN | APDS990X_EN_PEN;

	return apds990x_write_byte(chip, APDS990X_ENABLE, reg);
}