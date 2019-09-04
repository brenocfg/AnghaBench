#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct bnxt {scalar_t__ fw_ver_str; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX_DIR_EXT_NONE ; 
 int /*<<< orphan*/  BNX_DIR_ORDINAL_FIRST ; 
 int /*<<< orphan*/  BNX_DIR_TYPE_PKG_LOG ; 
 int /*<<< orphan*/  BNX_PKG_LOG_FIELD_IDX_PKG_VERSION ; 
 int FW_VER_STR_LEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ bnxt_find_nvram_item (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bnxt_get_nvram_item (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* bnxt_parse_pkglog (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (scalar_t__,int,char*,char*) ; 
 int strlen (scalar_t__) ; 

__attribute__((used)) static void bnxt_get_pkgver(struct net_device *dev)
{
	struct bnxt *bp = netdev_priv(dev);
	u16 index = 0;
	char *pkgver;
	u32 pkglen;
	u8 *pkgbuf;
	int len;

	if (bnxt_find_nvram_item(dev, BNX_DIR_TYPE_PKG_LOG,
				 BNX_DIR_ORDINAL_FIRST, BNX_DIR_EXT_NONE,
				 &index, NULL, &pkglen) != 0)
		return;

	pkgbuf = kzalloc(pkglen, GFP_KERNEL);
	if (!pkgbuf) {
		dev_err(&bp->pdev->dev, "Unable to allocate memory for pkg version, length = %u\n",
			pkglen);
		return;
	}

	if (bnxt_get_nvram_item(dev, index, 0, pkglen, pkgbuf))
		goto err;

	pkgver = bnxt_parse_pkglog(BNX_PKG_LOG_FIELD_IDX_PKG_VERSION, pkgbuf,
				   pkglen);
	if (pkgver && *pkgver != 0 && isdigit(*pkgver)) {
		len = strlen(bp->fw_ver_str);
		snprintf(bp->fw_ver_str + len, FW_VER_STR_LEN - len - 1,
			 "/pkg %s", pkgver);
	}
err:
	kfree(pkgbuf);
}