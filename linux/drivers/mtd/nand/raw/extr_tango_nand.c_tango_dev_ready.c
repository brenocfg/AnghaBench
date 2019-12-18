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
struct tango_nfc {scalar_t__ pbus_base; } ;
struct nand_chip {int /*<<< orphan*/  controller; } ;

/* Variables and functions */
 scalar_t__ PBUS_CS_CTRL ; 
 int PBUS_IORDY ; 
 int readl_relaxed (scalar_t__) ; 
 struct tango_nfc* to_tango_nfc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tango_dev_ready(struct nand_chip *chip)
{
	struct tango_nfc *nfc = to_tango_nfc(chip->controller);

	return readl_relaxed(nfc->pbus_base + PBUS_CS_CTRL) & PBUS_IORDY;
}