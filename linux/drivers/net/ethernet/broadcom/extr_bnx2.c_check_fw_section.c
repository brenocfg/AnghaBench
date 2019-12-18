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
struct firmware {int size; } ;
struct bnx2_fw_file_section {int /*<<< orphan*/  len; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_fw_section(const struct firmware *fw,
		 const struct bnx2_fw_file_section *section,
		 u32 alignment, bool non_empty)
{
	u32 offset = be32_to_cpu(section->offset);
	u32 len = be32_to_cpu(section->len);

	if ((offset == 0 && len != 0) || offset >= fw->size || offset & 3)
		return -EINVAL;
	if ((non_empty && len == 0) || len > fw->size - offset ||
	    len & (alignment - 1))
		return -EINVAL;
	return 0;
}