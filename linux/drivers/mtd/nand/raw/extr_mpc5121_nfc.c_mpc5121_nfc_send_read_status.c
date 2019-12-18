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
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_BUF_ADDR ; 
 int /*<<< orphan*/  NFC_CONFIG2 ; 
 int /*<<< orphan*/  NFC_RBA_MASK ; 
 int /*<<< orphan*/  NFC_STATUS ; 
 int /*<<< orphan*/  mpc5121_nfc_done (struct mtd_info*) ; 
 int /*<<< orphan*/  nfc_clear (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_write (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mpc5121_nfc_send_read_status(struct mtd_info *mtd)
{
	nfc_clear(mtd, NFC_BUF_ADDR, NFC_RBA_MASK);
	nfc_write(mtd, NFC_CONFIG2, NFC_STATUS);
	mpc5121_nfc_done(mtd);
}