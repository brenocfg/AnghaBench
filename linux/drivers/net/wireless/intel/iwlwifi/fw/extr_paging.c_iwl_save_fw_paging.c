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
struct iwl_fw_runtime {int dummy; } ;
struct fw_img {int dummy; } ;

/* Variables and functions */
 int iwl_alloc_fw_paging_mem (struct iwl_fw_runtime*,struct fw_img const*) ; 
 int iwl_fill_paging_mem (struct iwl_fw_runtime*,struct fw_img const*) ; 

__attribute__((used)) static int iwl_save_fw_paging(struct iwl_fw_runtime *fwrt,
			      const struct fw_img *fw)
{
	int ret;

	ret = iwl_alloc_fw_paging_mem(fwrt, fw);
	if (ret)
		return ret;

	return iwl_fill_paging_mem(fwrt, fw);
}