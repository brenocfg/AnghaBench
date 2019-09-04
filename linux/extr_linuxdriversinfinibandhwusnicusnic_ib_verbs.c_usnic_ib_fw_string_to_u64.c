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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */

__attribute__((used)) static void usnic_ib_fw_string_to_u64(char *fw_ver_str, u64 *fw_ver)
{
	*fw_ver = *((u64 *)fw_ver_str);
}