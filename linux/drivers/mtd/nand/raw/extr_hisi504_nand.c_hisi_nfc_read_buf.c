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
typedef  int /*<<< orphan*/  uint8_t ;
struct nand_chip {int dummy; } ;
struct hinfc_host {scalar_t__ offset; scalar_t__ buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 struct hinfc_host* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static void hisi_nfc_read_buf(struct nand_chip *chip, uint8_t *buf, int len)
{
	struct hinfc_host *host = nand_get_controller_data(chip);

	memcpy(buf, host->buffer + host->offset, len);
	host->offset += len;
}