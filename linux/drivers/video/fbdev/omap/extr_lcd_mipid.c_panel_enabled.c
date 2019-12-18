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
typedef  int u32 ;
struct mipid_device {TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPID_CMD_READ_DISP_STATUS ; 
 int __be32_to_cpu (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  mipid_read (struct mipid_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int panel_enabled(struct mipid_device *md)
{
	u32 disp_status;
	int enabled;

	mipid_read(md, MIPID_CMD_READ_DISP_STATUS, (u8 *)&disp_status, 4);
	disp_status = __be32_to_cpu(disp_status);
	enabled = (disp_status & (1 << 17)) && (disp_status & (1 << 10));
	dev_dbg(&md->spi->dev,
		"LCD panel %senabled by bootloader (status 0x%04x)\n",
		enabled ? "" : "not ", disp_status);
	return enabled;
}