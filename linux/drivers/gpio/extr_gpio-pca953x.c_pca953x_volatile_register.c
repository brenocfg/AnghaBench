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
typedef  int /*<<< orphan*/  u32 ;
struct pca953x_chip {int driver_data; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ PCA953X_TYPE ; 
 int /*<<< orphan*/  PCA953x_BANK_INPUT ; 
 int /*<<< orphan*/  PCA957x_BANK_INPUT ; 
 int /*<<< orphan*/  PCAL9xxx_BANK_IRQ_STAT ; 
 scalar_t__ PCA_CHIP_TYPE (int) ; 
 int PCA_PCAL ; 
 struct pca953x_chip* dev_get_drvdata (struct device*) ; 
 int pca953x_check_register (struct pca953x_chip*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool pca953x_volatile_register(struct device *dev, unsigned int reg)
{
	struct pca953x_chip *chip = dev_get_drvdata(dev);
	u32 bank;

	if (PCA_CHIP_TYPE(chip->driver_data) == PCA953X_TYPE)
		bank = PCA953x_BANK_INPUT;
	else
		bank = PCA957x_BANK_INPUT;

	if (chip->driver_data & PCA_PCAL)
		bank |= PCAL9xxx_BANK_IRQ_STAT;

	return pca953x_check_register(chip, reg, bank);
}