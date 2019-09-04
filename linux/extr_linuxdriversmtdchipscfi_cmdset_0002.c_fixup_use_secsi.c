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
struct mtd_info {void* _read_fact_prot_reg; void* _read_user_prot_reg; } ;

/* Variables and functions */
 void* cfi_amdstd_secsi_read ; 

__attribute__((used)) static void fixup_use_secsi(struct mtd_info *mtd)
{
	/* Setup for chips with a secsi area */
	mtd->_read_user_prot_reg = cfi_amdstd_secsi_read;
	mtd->_read_fact_prot_reg = cfi_amdstd_secsi_read;
}