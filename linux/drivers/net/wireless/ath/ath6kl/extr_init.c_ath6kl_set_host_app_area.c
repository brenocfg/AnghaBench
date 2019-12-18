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
typedef  int /*<<< orphan*/  u32 ;
struct host_app_area {int /*<<< orphan*/  wmi_protocol_ver; } ;
struct ath6kl {int /*<<< orphan*/  target_type; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  HI_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARG_VTOP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WMI_PROTOCOL_VERSION ; 
 scalar_t__ ath6kl_diag_read32 (struct ath6kl*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ath6kl_diag_write (struct ath6kl*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ath6kl_get_hi_item_addr (struct ath6kl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hi_app_host_interest ; 

__attribute__((used)) static int ath6kl_set_host_app_area(struct ath6kl *ar)
{
	u32 address, data;
	struct host_app_area host_app_area;

	/* Fetch the address of the host_app_area_s
	 * instance in the host interest area */
	address = ath6kl_get_hi_item_addr(ar, HI_ITEM(hi_app_host_interest));
	address = TARG_VTOP(ar->target_type, address);

	if (ath6kl_diag_read32(ar, address, &data))
		return -EIO;

	address = TARG_VTOP(ar->target_type, data);
	host_app_area.wmi_protocol_ver = cpu_to_le32(WMI_PROTOCOL_VERSION);
	if (ath6kl_diag_write(ar, address, (u8 *) &host_app_area,
			      sizeof(struct host_app_area)))
		return -EIO;

	return 0;
}