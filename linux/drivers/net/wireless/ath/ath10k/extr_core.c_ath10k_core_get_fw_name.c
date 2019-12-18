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
struct TYPE_2__ {int bus; } ;
struct ath10k {TYPE_1__ hif; } ;

/* Variables and functions */
#define  ATH10K_BUS_AHB 132 
#define  ATH10K_BUS_PCI 131 
#define  ATH10K_BUS_SDIO 130 
#define  ATH10K_BUS_SNOC 129 
#define  ATH10K_BUS_USB 128 
 int /*<<< orphan*/  ATH10K_FW_FILE_BASE ; 
 int /*<<< orphan*/  ath10k_bus_str (int) ; 
 int /*<<< orphan*/  scnprintf (char*,size_t,char*,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static void ath10k_core_get_fw_name(struct ath10k *ar, char *fw_name,
				    size_t fw_name_len, int fw_api)
{
	switch (ar->hif.bus) {
	case ATH10K_BUS_SDIO:
	case ATH10K_BUS_USB:
		scnprintf(fw_name, fw_name_len, "%s-%s-%d.bin",
			  ATH10K_FW_FILE_BASE, ath10k_bus_str(ar->hif.bus),
			  fw_api);
		break;
	case ATH10K_BUS_PCI:
	case ATH10K_BUS_AHB:
	case ATH10K_BUS_SNOC:
		scnprintf(fw_name, fw_name_len, "%s-%d.bin",
			  ATH10K_FW_FILE_BASE, fw_api);
		break;
	}
}