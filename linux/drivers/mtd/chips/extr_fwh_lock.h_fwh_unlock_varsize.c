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
typedef  int /*<<< orphan*/  uint64_t ;
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  FWH_XXLOCK_ONEBLOCK_UNLOCK ; 
 int cfi_varsize_frob (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  fwh_xxlock_oneblock ; 

__attribute__((used)) static int fwh_unlock_varsize(struct mtd_info *mtd, loff_t ofs, uint64_t len)
{
	int ret;

	ret = cfi_varsize_frob(mtd, fwh_xxlock_oneblock, ofs, len,
		(void *)&FWH_XXLOCK_ONEBLOCK_UNLOCK);

	return ret;
}