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
struct atmel_aes_dev {int /*<<< orphan*/  iclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_CR ; 
 int AES_CR_SWRST ; 
 int /*<<< orphan*/  AES_MR ; 
 int AES_MR_CKEY_OFFSET ; 
 int /*<<< orphan*/  atmel_aes_write (struct atmel_aes_dev*,int /*<<< orphan*/ ,int) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_aes_hw_init(struct atmel_aes_dev *dd)
{
	int err;

	err = clk_enable(dd->iclk);
	if (err)
		return err;

	atmel_aes_write(dd, AES_CR, AES_CR_SWRST);
	atmel_aes_write(dd, AES_MR, 0xE << AES_MR_CKEY_OFFSET);

	return 0;
}