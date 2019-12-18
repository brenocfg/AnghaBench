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
struct s3fwrn5_fw_cmd_get_bootinfo_rsp {int /*<<< orphan*/ * hw_version; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
s3fwrn5_fw_is_custom(struct s3fwrn5_fw_cmd_get_bootinfo_rsp *bootinfo)
{
	return !!bootinfo->hw_version[2];
}