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
typedef  int u32 ;
struct pca953x_chip {int driver_data; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ PCA953X_TYPE ; 
 int PCA953x_BANK_CONFIG ; 
 int PCA953x_BANK_INPUT ; 
 int PCA953x_BANK_OUTPUT ; 
 int PCA953x_BANK_POLARITY ; 
 int PCA957x_BANK_BUSHOLD ; 
 int PCA957x_BANK_CONFIG ; 
 int PCA957x_BANK_INPUT ; 
 int PCA957x_BANK_OUTPUT ; 
 int PCA957x_BANK_POLARITY ; 
 int PCAL9xxx_BANK_IN_LATCH ; 
 int PCAL9xxx_BANK_IRQ_MASK ; 
 int PCAL9xxx_BANK_IRQ_STAT ; 
 int PCAL9xxx_BANK_PULL_EN ; 
 int PCAL9xxx_BANK_PULL_SEL ; 
 scalar_t__ PCA_CHIP_TYPE (int) ; 
 int PCA_PCAL ; 
 struct pca953x_chip* dev_get_drvdata (struct device*) ; 
 int pca953x_check_register (struct pca953x_chip*,unsigned int,int) ; 

__attribute__((used)) static bool pca953x_readable_register(struct device *dev, unsigned int reg)
{
	struct pca953x_chip *chip = dev_get_drvdata(dev);
	u32 bank;

	if (PCA_CHIP_TYPE(chip->driver_data) == PCA953X_TYPE) {
		bank = PCA953x_BANK_INPUT | PCA953x_BANK_OUTPUT |
		       PCA953x_BANK_POLARITY | PCA953x_BANK_CONFIG;
	} else {
		bank = PCA957x_BANK_INPUT | PCA957x_BANK_OUTPUT |
		       PCA957x_BANK_POLARITY | PCA957x_BANK_CONFIG |
		       PCA957x_BANK_BUSHOLD;
	}

	if (chip->driver_data & PCA_PCAL) {
		bank |= PCAL9xxx_BANK_IN_LATCH | PCAL9xxx_BANK_PULL_EN |
			PCAL9xxx_BANK_PULL_SEL | PCAL9xxx_BANK_IRQ_MASK |
			PCAL9xxx_BANK_IRQ_STAT;
	}

	return pca953x_check_register(chip, reg, bank);
}