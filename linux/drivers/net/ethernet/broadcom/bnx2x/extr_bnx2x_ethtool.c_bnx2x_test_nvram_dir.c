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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct code_entry {size_t code_attribute; int /*<<< orphan*/  nvm_start_addr; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BNX2X_MSG_ETHTOOL ; 
 int BNX2X_MSG_NVM ; 
 size_t CODE_IMAGE_LENGTH_MASK ; 
 scalar_t__ CODE_IMAGE_TYPE_MASK ; 
 scalar_t__ CODE_IMAGE_VNTAG_PROFILES_DATA ; 
 int /*<<< orphan*/  DP (int,char*,scalar_t__,int) ; 
 int bnx2x_nvram_crc (struct bnx2x*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2x_test_nvram_dir(struct bnx2x *bp,
				struct code_entry *entry,
				u8 *buff)
{
	size_t size = entry->code_attribute & CODE_IMAGE_LENGTH_MASK;
	u32 type = entry->code_attribute & CODE_IMAGE_TYPE_MASK;
	int rc;

	/* Zero-length images and AFEX profiles do not have CRC */
	if (size == 0 || type == CODE_IMAGE_VNTAG_PROFILES_DATA)
		return 0;

	rc = bnx2x_nvram_crc(bp, entry->nvm_start_addr, size, buff);
	if (rc)
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "image %x has failed crc test (rc %d)\n", type, rc);

	return rc;
}