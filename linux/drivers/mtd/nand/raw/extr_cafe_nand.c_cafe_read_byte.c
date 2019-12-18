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
typedef  int /*<<< orphan*/  uint8_t ;
struct nand_chip {int dummy; } ;
struct cafe_priv {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cafe_dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cafe_read_buf (struct nand_chip*,int /*<<< orphan*/ *,int) ; 
 struct cafe_priv* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static uint8_t cafe_read_byte(struct nand_chip *chip)
{
	struct cafe_priv *cafe = nand_get_controller_data(chip);
	uint8_t d;

	cafe_read_buf(chip, &d, 1);
	cafe_dev_dbg(&cafe->pdev->dev, "Read %02x\n", d);

	return d;
}