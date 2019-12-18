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
typedef  scalar_t__ u32 ;
struct qlcnic_flt_entry {scalar_t__ start_addr; } ;
struct qlcnic_adapter {TYPE_1__* pdev; TYPE_2__* ahw; } ;
struct TYPE_4__ {scalar_t__ revision_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  QLCNIC_B0_FW_IMAGE_REGION ; 
 int /*<<< orphan*/  QLCNIC_C0_FW_IMAGE_REGION ; 
 scalar_t__ QLCNIC_DECODE_VERSION (scalar_t__) ; 
 scalar_t__ QLCNIC_FW_VERSION_OFFSET ; 
 scalar_t__ QLCNIC_MIN_FW_VERSION ; 
 scalar_t__ QLCNIC_P3P_C0 ; 
 int /*<<< orphan*/  _build (scalar_t__) ; 
 int /*<<< orphan*/  _major (scalar_t__) ; 
 int /*<<< orphan*/  _minor (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qlcnic_get_flt_entry (struct qlcnic_adapter*,int /*<<< orphan*/ ,struct qlcnic_flt_entry*) ; 
 int /*<<< orphan*/  qlcnic_rom_fast_read (struct qlcnic_adapter*,scalar_t__,int*) ; 

int
qlcnic_check_flash_fw_ver(struct qlcnic_adapter *adapter)
{
	struct qlcnic_flt_entry fw_entry;
	u32 ver = -1, min_ver;
	int ret;

	if (adapter->ahw->revision_id == QLCNIC_P3P_C0)
		ret = qlcnic_get_flt_entry(adapter, QLCNIC_C0_FW_IMAGE_REGION,
						 &fw_entry);
	else
		ret = qlcnic_get_flt_entry(adapter, QLCNIC_B0_FW_IMAGE_REGION,
						 &fw_entry);

	if (!ret)
		/* 0-4:-signature,  4-8:-fw version */
		qlcnic_rom_fast_read(adapter, fw_entry.start_addr + 4,
				     (int *)&ver);
	else
		qlcnic_rom_fast_read(adapter, QLCNIC_FW_VERSION_OFFSET,
				     (int *)&ver);

	ver = QLCNIC_DECODE_VERSION(ver);
	min_ver = QLCNIC_MIN_FW_VERSION;

	if (ver < min_ver) {
		dev_err(&adapter->pdev->dev,
			"firmware version %d.%d.%d unsupported."
			"Min supported version %d.%d.%d\n",
			_major(ver), _minor(ver), _build(ver),
			_major(min_ver), _minor(min_ver), _build(min_ver));
		return -EINVAL;
	}

	return 0;
}