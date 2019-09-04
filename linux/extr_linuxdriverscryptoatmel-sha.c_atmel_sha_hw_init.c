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
struct atmel_sha_dev {int flags; scalar_t__ err; int /*<<< orphan*/  iclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHA_CR ; 
 int /*<<< orphan*/  SHA_CR_SWRST ; 
 int SHA_FLAGS_INIT ; 
 int /*<<< orphan*/  atmel_sha_write (struct atmel_sha_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_sha_hw_init(struct atmel_sha_dev *dd)
{
	int err;

	err = clk_enable(dd->iclk);
	if (err)
		return err;

	if (!(SHA_FLAGS_INIT & dd->flags)) {
		atmel_sha_write(dd, SHA_CR, SHA_CR_SWRST);
		dd->flags |= SHA_FLAGS_INIT;
		dd->err = 0;
	}

	return 0;
}