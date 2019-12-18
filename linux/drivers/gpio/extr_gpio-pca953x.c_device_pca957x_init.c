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
typedef  int /*<<< orphan*/  u32 ;
struct pca953x_chip {int dummy; } ;

/* Variables and functions */
 int MAX_BANK ; 
 int /*<<< orphan*/  NBANK (struct pca953x_chip*) ; 
 int /*<<< orphan*/  PCA957X_BKEN ; 
 int device_pca95xx_init (struct pca953x_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int pca953x_write_regs (struct pca953x_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int device_pca957x_init(struct pca953x_chip *chip, u32 invert)
{
	int ret;
	u8 val[MAX_BANK];

	ret = device_pca95xx_init(chip, invert);
	if (ret)
		goto out;

	/* To enable register 6, 7 to control pull up and pull down */
	memset(val, 0x02, NBANK(chip));
	ret = pca953x_write_regs(chip, PCA957X_BKEN, val);
	if (ret)
		goto out;

	return 0;
out:
	return ret;
}