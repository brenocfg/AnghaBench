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
struct firmware {int dummy; } ;
struct bnx2_mips_fw_file_entry {int /*<<< orphan*/  rodata; int /*<<< orphan*/  data; int /*<<< orphan*/  text; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ check_fw_section (struct firmware const*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int
check_mips_fw_entry(const struct firmware *fw,
		    const struct bnx2_mips_fw_file_entry *entry)
{
	if (check_fw_section(fw, &entry->text, 4, true) ||
	    check_fw_section(fw, &entry->data, 4, false) ||
	    check_fw_section(fw, &entry->rodata, 4, false))
		return -EINVAL;
	return 0;
}