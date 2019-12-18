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

/* Variables and functions */
 int /*<<< orphan*/  sunxi_nfc_randomizer_config (struct nand_chip*,int,int) ; 
 int /*<<< orphan*/  sunxi_nfc_randomizer_disable (struct nand_chip*) ; 
 int /*<<< orphan*/  sunxi_nfc_randomizer_enable (struct nand_chip*) ; 
 int /*<<< orphan*/  sunxi_nfc_write_buf (struct nand_chip*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void sunxi_nfc_randomizer_write_buf(struct nand_chip *nand,
					   const uint8_t *buf, int len,
					   bool ecc, int page)
{
	sunxi_nfc_randomizer_config(nand, page, ecc);
	sunxi_nfc_randomizer_enable(nand);
	sunxi_nfc_write_buf(nand, buf, len);
	sunxi_nfc_randomizer_disable(nand);
}