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
struct platform_device {int dummy; } ;
struct ingenic_nfc {scalar_t__ ecc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ingenic_ecc_release (scalar_t__) ; 
 int /*<<< orphan*/  ingenic_nand_cleanup_chips (struct ingenic_nfc*) ; 
 struct ingenic_nfc* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ingenic_nand_remove(struct platform_device *pdev)
{
	struct ingenic_nfc *nfc = platform_get_drvdata(pdev);

	if (nfc->ecc)
		ingenic_ecc_release(nfc->ecc);

	ingenic_nand_cleanup_chips(nfc);

	return 0;
}