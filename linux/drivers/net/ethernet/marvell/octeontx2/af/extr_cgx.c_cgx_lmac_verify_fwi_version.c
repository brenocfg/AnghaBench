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
typedef  int /*<<< orphan*/  u64 ;
struct device {int dummy; } ;
struct cgx {int /*<<< orphan*/  lmac_count; TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int CGX_FIRMWARE_MAJOR_VER ; 
 int CGX_FIRMWARE_MINOR_VER ; 
 int EIO ; 
 int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESP_MAJOR_VER ; 
 int /*<<< orphan*/  RESP_MINOR_VER ; 
 int cgx_fwi_read_version (int /*<<< orphan*/ *,struct cgx*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int) ; 

__attribute__((used)) static int cgx_lmac_verify_fwi_version(struct cgx *cgx)
{
	struct device *dev = &cgx->pdev->dev;
	int major_ver, minor_ver;
	u64 resp;
	int err;

	if (!cgx->lmac_count)
		return 0;

	err = cgx_fwi_read_version(&resp, cgx);
	if (err)
		return err;

	major_ver = FIELD_GET(RESP_MAJOR_VER, resp);
	minor_ver = FIELD_GET(RESP_MINOR_VER, resp);
	dev_dbg(dev, "Firmware command interface version = %d.%d\n",
		major_ver, minor_ver);
	if (major_ver != CGX_FIRMWARE_MAJOR_VER ||
	    minor_ver != CGX_FIRMWARE_MINOR_VER)
		return -EIO;
	else
		return 0;
}