#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {char* check_vmid; char* cmd; char* queue_id; char* simd_id; char* mode; char* vm_id; char* wave_id; } ;
struct TYPE_10__ {char* vm_id; } ;
union SQ_CMD_BITS {scalar_t__ u32All; TYPE_6__ bitfields; TYPE_1__ bits; } ;
struct TYPE_16__ {char* instance_broadcast_writes; char* instance_index; char* se_broadcast_writes; char* se_index; char* sh_index; char* sh_broadcast_writes; } ;
union GRBM_GFX_INDEX_BITS {int /*<<< orphan*/  u32All; TYPE_7__ bitfields; } ;
struct TYPE_14__ {char* vmid; } ;
struct kfd_process_device {TYPE_5__ qpd; } ;
struct kfd_dbgdev {TYPE_9__* dev; } ;
struct TYPE_11__ {char* Value; } ;
struct TYPE_12__ {TYPE_2__ WaveMsgInfoGen2; } ;
struct TYPE_13__ {TYPE_3__ DbgWaveMsg; } ;
struct dbg_wave_control_info {char* mode; char* operand; char* trapId; TYPE_4__ dbgWave_msg; int /*<<< orphan*/  process; } ;
struct TYPE_18__ {int /*<<< orphan*/  kgd; TYPE_8__* kfd2kgd; } ;
struct TYPE_17__ {int (* wave_control_execute ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ;} ;

/* Variables and functions */
 int EFAULT ; 
 int dbgdev_wave_control_set_registers (struct dbg_wave_control_info*,union SQ_CMD_BITS*,union GRBM_GFX_INDEX_BITS*) ; 
 struct kfd_process_device* kfd_get_process_device_data (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int dbgdev_wave_control_nodiq(struct kfd_dbgdev *dbgdev,
					struct dbg_wave_control_info *wac_info)
{
	int status;
	union SQ_CMD_BITS reg_sq_cmd;
	union GRBM_GFX_INDEX_BITS reg_gfx_index;
	struct kfd_process_device *pdd;

	reg_sq_cmd.u32All = 0;

	/* taking the VMID for that process on the safe way using PDD */
	pdd = kfd_get_process_device_data(dbgdev->dev, wac_info->process);

	if (!pdd) {
		pr_err("Failed to get pdd for wave control no DIQ\n");
		return -EFAULT;
	}
	status = dbgdev_wave_control_set_registers(wac_info, &reg_sq_cmd,
							&reg_gfx_index);
	if (status) {
		pr_err("Failed to set wave control registers\n");
		return status;
	}

	/* for non DIQ we need to patch the VMID: */

	reg_sq_cmd.bits.vm_id = pdd->qpd.vmid;

	pr_debug("\t\t %30s\n", "* * * * * * * * * * * * * * * * * *");

	pr_debug("\t\t mode      is: %u\n", wac_info->mode);
	pr_debug("\t\t operand   is: %u\n", wac_info->operand);
	pr_debug("\t\t trap id   is: %u\n", wac_info->trapId);
	pr_debug("\t\t msg value is: %u\n",
			wac_info->dbgWave_msg.DbgWaveMsg.WaveMsgInfoGen2.Value);
	pr_debug("\t\t vmid      is: %u\n", pdd->qpd.vmid);

	pr_debug("\t\t chk_vmid  is : %u\n", reg_sq_cmd.bitfields.check_vmid);
	pr_debug("\t\t command   is : %u\n", reg_sq_cmd.bitfields.cmd);
	pr_debug("\t\t queue id  is : %u\n", reg_sq_cmd.bitfields.queue_id);
	pr_debug("\t\t simd id   is : %u\n", reg_sq_cmd.bitfields.simd_id);
	pr_debug("\t\t mode      is : %u\n", reg_sq_cmd.bitfields.mode);
	pr_debug("\t\t vm_id     is : %u\n", reg_sq_cmd.bitfields.vm_id);
	pr_debug("\t\t wave_id   is : %u\n", reg_sq_cmd.bitfields.wave_id);

	pr_debug("\t\t ibw       is : %u\n",
			reg_gfx_index.bitfields.instance_broadcast_writes);
	pr_debug("\t\t ii        is : %u\n",
			reg_gfx_index.bitfields.instance_index);
	pr_debug("\t\t sebw      is : %u\n",
			reg_gfx_index.bitfields.se_broadcast_writes);
	pr_debug("\t\t se_ind    is : %u\n", reg_gfx_index.bitfields.se_index);
	pr_debug("\t\t sh_ind    is : %u\n", reg_gfx_index.bitfields.sh_index);
	pr_debug("\t\t sbw       is : %u\n",
			reg_gfx_index.bitfields.sh_broadcast_writes);

	pr_debug("\t\t %30s\n", "* * * * * * * * * * * * * * * * * *");

	return dbgdev->dev->kfd2kgd->wave_control_execute(dbgdev->dev->kgd,
							reg_gfx_index.u32All,
							reg_sq_cmd.u32All);
}