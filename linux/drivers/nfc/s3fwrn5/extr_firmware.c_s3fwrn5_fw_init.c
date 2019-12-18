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
struct TYPE_2__ {int /*<<< orphan*/ * fw; } ;
struct s3fwrn5_fw_info {int parity; int /*<<< orphan*/  completion; int /*<<< orphan*/  fw_name; TYPE_1__ fw; int /*<<< orphan*/ * rsp; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

void s3fwrn5_fw_init(struct s3fwrn5_fw_info *fw_info, const char *fw_name)
{
	fw_info->parity = 0x00;
	fw_info->rsp = NULL;
	fw_info->fw.fw = NULL;
	strcpy(fw_info->fw_name, fw_name);
	init_completion(&fw_info->completion);
}