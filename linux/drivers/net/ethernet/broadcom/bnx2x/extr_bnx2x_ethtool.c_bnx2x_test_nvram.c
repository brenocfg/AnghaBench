#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct crc_pair {int member_0; int member_1; } ;
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  magic ;
struct TYPE_3__ {int /*<<< orphan*/  config2; } ;
struct TYPE_4__ {TYPE_1__ shared_hw_config; } ;

/* Variables and functions */
 int BNX2X_MSG_ETHTOOL ; 
 int BNX2X_MSG_NVM ; 
 scalar_t__ BP_NOMCP (struct bnx2x*) ; 
 int /*<<< orphan*/  CHIP_IS_57811xx (struct bnx2x*) ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bnx2x*) ; 
 int /*<<< orphan*/  CRC_BUFF_SIZE ; 
 int /*<<< orphan*/  DP (int,char*,...) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SHARED_HW_CFG_HIDE_PORT1 ; 
 int SHMEM_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int bnx2x_nvram_read32 (struct bnx2x*,int /*<<< orphan*/ ,int*,int) ; 
 int bnx2x_test_nvram_dirs (struct bnx2x*,int /*<<< orphan*/ *) ; 
 int bnx2x_test_nvram_tbl (struct bnx2x*,struct crc_pair const*,int /*<<< orphan*/ *) ; 
 TYPE_2__ dev_info ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_test_nvram(struct bnx2x *bp)
{
	static const struct crc_pair nvram_tbl[] = {
		{     0,  0x14 }, /* bootstrap */
		{  0x14,  0xec }, /* dir */
		{ 0x100, 0x350 }, /* manuf_info */
		{ 0x450,  0xf0 }, /* feature_info */
		{ 0x640,  0x64 }, /* upgrade_key_info */
		{ 0x708,  0x70 }, /* manuf_key_info */
		{     0,     0 }
	};
	static const struct crc_pair nvram_tbl2[] = {
		{ 0x7e8, 0x350 }, /* manuf_info2 */
		{ 0xb38,  0xf0 }, /* feature_info */
		{     0,     0 }
	};

	u8 *buf;
	int rc;
	u32 magic;

	if (BP_NOMCP(bp))
		return 0;

	buf = kmalloc(CRC_BUFF_SIZE, GFP_KERNEL);
	if (!buf) {
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM, "kmalloc failed\n");
		rc = -ENOMEM;
		goto test_nvram_exit;
	}

	rc = bnx2x_nvram_read32(bp, 0, &magic, sizeof(magic));
	if (rc) {
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "magic value read (rc %d)\n", rc);
		goto test_nvram_exit;
	}

	if (magic != 0x669955aa) {
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "wrong magic value (0x%08x)\n", magic);
		rc = -ENODEV;
		goto test_nvram_exit;
	}

	DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM, "Port 0 CRC test-set\n");
	rc = bnx2x_test_nvram_tbl(bp, nvram_tbl, buf);
	if (rc)
		goto test_nvram_exit;

	if (!CHIP_IS_E1x(bp) && !CHIP_IS_57811xx(bp)) {
		u32 hide = SHMEM_RD(bp, dev_info.shared_hw_config.config2) &
			   SHARED_HW_CFG_HIDE_PORT1;

		if (!hide) {
			DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
			   "Port 1 CRC test-set\n");
			rc = bnx2x_test_nvram_tbl(bp, nvram_tbl2, buf);
			if (rc)
				goto test_nvram_exit;
		}
	}

	rc = bnx2x_test_nvram_dirs(bp, buf);

test_nvram_exit:
	kfree(buf);
	return rc;
}