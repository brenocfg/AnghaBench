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
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int cfi_amdstd_otp_walk (struct mtd_info*,int /*<<< orphan*/ ,size_t,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  do_otp_lock ; 

__attribute__((used)) static int cfi_amdstd_lock_user_prot_reg(struct mtd_info *mtd, loff_t from,
					 size_t len)
{
	size_t retlen;
	return cfi_amdstd_otp_walk(mtd, from, len, &retlen, NULL,
				   do_otp_lock, 1);
}