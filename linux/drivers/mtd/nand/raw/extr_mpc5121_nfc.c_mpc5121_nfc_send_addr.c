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
typedef  int /*<<< orphan*/  u16 ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_ADDRESS ; 
 int /*<<< orphan*/  NFC_CONFIG2 ; 
 int /*<<< orphan*/  NFC_FLASH_ADDR ; 
 int /*<<< orphan*/  mpc5121_nfc_done (struct mtd_info*) ; 
 int /*<<< orphan*/  nfc_write (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mpc5121_nfc_send_addr(struct mtd_info *mtd, u16 addr)
{
	nfc_write(mtd, NFC_FLASH_ADDR, addr);
	nfc_write(mtd, NFC_CONFIG2, NFC_ADDRESS);
	mpc5121_nfc_done(mtd);
}