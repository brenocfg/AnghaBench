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
struct hfi1_devdata {size_t hfi1_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE_SPICO_SMASK ; 
 int /*<<< orphan*/  MISC_CFG_FW_CTRL ; 
 int /*<<< orphan*/  SBUS_MASTER_BROADCAST ; 
 int SPICO_FABRIC ; 
 int SPICO_SBUS ; 
 int /*<<< orphan*/  WRITE_SBUS_RECEIVER ; 
 int /*<<< orphan*/  dd_dev_info (struct hfi1_devdata*,char*,char*,char*) ; 
 int /*<<< orphan*/ * fabric_serdes_broadcast ; 
 int /*<<< orphan*/  is_ax (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  sbus_request (struct hfi1_devdata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void turn_off_spicos(struct hfi1_devdata *dd, int flags)
{
	/* only needed on A0 */
	if (!is_ax(dd))
		return;

	dd_dev_info(dd, "Turning off spicos:%s%s\n",
		    flags & SPICO_SBUS ? " SBus" : "",
		    flags & SPICO_FABRIC ? " fabric" : "");

	write_csr(dd, MISC_CFG_FW_CTRL, ENABLE_SPICO_SMASK);
	/* disable SBus spico */
	if (flags & SPICO_SBUS)
		sbus_request(dd, SBUS_MASTER_BROADCAST, 0x01,
			     WRITE_SBUS_RECEIVER, 0x00000040);

	/* disable the fabric serdes spicos */
	if (flags & SPICO_FABRIC)
		sbus_request(dd, fabric_serdes_broadcast[dd->hfi1_id],
			     0x07, WRITE_SBUS_RECEIVER, 0x00000000);
	write_csr(dd, MISC_CFG_FW_CTRL, 0);
}