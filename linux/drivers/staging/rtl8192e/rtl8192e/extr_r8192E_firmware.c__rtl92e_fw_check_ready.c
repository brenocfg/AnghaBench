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
typedef  int u8 ;
struct rt_firmware {int /*<<< orphan*/  status; } ;
struct r8192_priv {struct rt_firmware* pFirmware; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_FIRMWARE ; 
 int /*<<< orphan*/  CPU_GEN_FIRM_RDY ; 
#define  FW_INIT_STEP0_BOOT 130 
#define  FW_INIT_STEP1_MAIN 129 
#define  FW_INIT_STEP2_DATA 128 
 int /*<<< orphan*/  FW_STATUS_1_MOVE_BOOT_CODE ; 
 int /*<<< orphan*/  FW_STATUS_2_MOVE_MAIN_CODE ; 
 int /*<<< orphan*/  FW_STATUS_3_TURNON_CPU ; 
 int /*<<< orphan*/  FW_STATUS_4_MOVE_DATA_CODE ; 
 int /*<<< orphan*/  FW_STATUS_5_READY ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int) ; 
 int _rtl92e_fw_boot_cpu (struct net_device*) ; 
 int _rtl92e_wait_for_fw (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static bool _rtl92e_fw_check_ready(struct net_device *dev,
				   u8 load_fw_status)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	struct rt_firmware *pfirmware = priv->pFirmware;
	bool rt_status  = true;

	switch (load_fw_status) {
	case FW_INIT_STEP0_BOOT:
		pfirmware->status = FW_STATUS_1_MOVE_BOOT_CODE;
		break;

	case FW_INIT_STEP1_MAIN:
		pfirmware->status = FW_STATUS_2_MOVE_MAIN_CODE;

		rt_status = _rtl92e_fw_boot_cpu(dev);
		if (rt_status)
			pfirmware->status = FW_STATUS_3_TURNON_CPU;
		else
			netdev_dbg(dev, "_rtl92e_fw_boot_cpu fail!\n");

		break;

	case FW_INIT_STEP2_DATA:
		pfirmware->status = FW_STATUS_4_MOVE_DATA_CODE;
		mdelay(1);

		rt_status = _rtl92e_wait_for_fw(dev, CPU_GEN_FIRM_RDY, 20);
		if (rt_status)
			pfirmware->status = FW_STATUS_5_READY;
		else
			RT_TRACE(COMP_FIRMWARE,
				 "_rtl92e_is_fw_ready fail(%d)!\n",
				 rt_status);
		break;
	default:
		rt_status = false;
		netdev_dbg(dev, "Unknown firmware status");
		break;
	}

	return rt_status;
}