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
struct atmel_aes_dev {int buflen; int /*<<< orphan*/  dev; void* buf; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  ATMEL_AES_BUFFER_ORDER ; 
 int ATMEL_AES_BUFFER_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int atmel_aes_buff_init(struct atmel_aes_dev *dd)
{
	dd->buf = (void *)__get_free_pages(GFP_KERNEL, ATMEL_AES_BUFFER_ORDER);
	dd->buflen = ATMEL_AES_BUFFER_SIZE;
	dd->buflen &= ~(AES_BLOCK_SIZE - 1);

	if (!dd->buf) {
		dev_err(dd->dev, "unable to alloc pages.\n");
		return -ENOMEM;
	}

	return 0;
}