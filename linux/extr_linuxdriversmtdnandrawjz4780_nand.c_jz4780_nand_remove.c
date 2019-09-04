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
struct jz4780_nand_controller {scalar_t__ bch; } ;

/* Variables and functions */
 int /*<<< orphan*/  jz4780_bch_release (scalar_t__) ; 
 int /*<<< orphan*/  jz4780_nand_cleanup_chips (struct jz4780_nand_controller*) ; 
 struct jz4780_nand_controller* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int jz4780_nand_remove(struct platform_device *pdev)
{
	struct jz4780_nand_controller *nfc = platform_get_drvdata(pdev);

	if (nfc->bch)
		jz4780_bch_release(nfc->bch);

	jz4780_nand_cleanup_chips(nfc);

	return 0;
}