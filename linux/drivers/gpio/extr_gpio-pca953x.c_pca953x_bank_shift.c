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
struct TYPE_2__ {int ngpio; } ;
struct pca953x_chip {TYPE_1__ gpio_chip; } ;

/* Variables and functions */
 int BANK_SZ ; 
 int fls (int) ; 

__attribute__((used)) static int pca953x_bank_shift(struct pca953x_chip *chip)
{
	return fls((chip->gpio_chip.ngpio - 1) / BANK_SZ);
}