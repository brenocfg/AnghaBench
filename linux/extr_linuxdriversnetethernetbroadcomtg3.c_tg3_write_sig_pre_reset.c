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
struct tg3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASF_NEW_HANDSHAKE ; 
 int /*<<< orphan*/  DRV_STATE_START ; 
 int /*<<< orphan*/  DRV_STATE_SUSPEND ; 
 int /*<<< orphan*/  DRV_STATE_UNLOAD ; 
 int /*<<< orphan*/  NIC_SRAM_FIRMWARE_MBOX ; 
 int /*<<< orphan*/  NIC_SRAM_FIRMWARE_MBOX_MAGIC1 ; 
 int /*<<< orphan*/  NIC_SRAM_FW_DRV_STATE_MBOX ; 
#define  RESET_KIND_INIT 130 
#define  RESET_KIND_SHUTDOWN 129 
#define  RESET_KIND_SUSPEND 128 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_write_mem (struct tg3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_write_sig_pre_reset(struct tg3 *tp, int kind)
{
	tg3_write_mem(tp, NIC_SRAM_FIRMWARE_MBOX,
		      NIC_SRAM_FIRMWARE_MBOX_MAGIC1);

	if (tg3_flag(tp, ASF_NEW_HANDSHAKE)) {
		switch (kind) {
		case RESET_KIND_INIT:
			tg3_write_mem(tp, NIC_SRAM_FW_DRV_STATE_MBOX,
				      DRV_STATE_START);
			break;

		case RESET_KIND_SHUTDOWN:
			tg3_write_mem(tp, NIC_SRAM_FW_DRV_STATE_MBOX,
				      DRV_STATE_UNLOAD);
			break;

		case RESET_KIND_SUSPEND:
			tg3_write_mem(tp, NIC_SRAM_FW_DRV_STATE_MBOX,
				      DRV_STATE_SUSPEND);
			break;

		default:
			break;
		}
	}
}