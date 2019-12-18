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
struct wd719x {int dummy; } ;
struct eeprom_93cx6 {int reg_data_out; struct wd719x* data; } ;

/* Variables and functions */
 int WD719X_EE_DO ; 
 int /*<<< orphan*/  WD719X_PCI_GPIO_DATA ; 
 int wd719x_readb (struct wd719x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wd719x_eeprom_reg_read(struct eeprom_93cx6 *eeprom)
{
	struct wd719x *wd = eeprom->data;
	u8 reg = wd719x_readb(wd, WD719X_PCI_GPIO_DATA);

	eeprom->reg_data_out = reg & WD719X_EE_DO;
}