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
struct atmel_aes_dev {int /*<<< orphan*/  iclk; int /*<<< orphan*/  hw_version; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_aes_get_version (struct atmel_aes_dev*) ; 
 int atmel_aes_hw_init (struct atmel_aes_dev*) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_aes_hw_version_init(struct atmel_aes_dev *dd)
{
	int err;

	err = atmel_aes_hw_init(dd);
	if (err)
		return err;

	dd->hw_version = atmel_aes_get_version(dd);

	dev_info(dd->dev, "version: 0x%x\n", dd->hw_version);

	clk_disable(dd->iclk);
	return 0;
}