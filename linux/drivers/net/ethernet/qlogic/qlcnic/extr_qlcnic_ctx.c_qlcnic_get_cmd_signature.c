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
typedef  int u32 ;
struct qlcnic_hardware_context {int pci_func; int fw_hal_version; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 qlcnic_get_cmd_signature(struct qlcnic_hardware_context *ahw)
{
	return (ahw->pci_func & 0xff) | ((ahw->fw_hal_version & 0xff) << 8) |
	       (0xcafe << 16);
}