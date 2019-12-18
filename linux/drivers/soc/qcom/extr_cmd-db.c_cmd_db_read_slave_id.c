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
struct entry_header {int /*<<< orphan*/  addr; } ;
typedef  enum cmd_db_hw_type { ____Placeholder_cmd_db_hw_type } cmd_db_hw_type ;

/* Variables and functions */
 int CMD_DB_HW_INVALID ; 
 int SLAVE_ID_MASK ; 
 int SLAVE_ID_SHIFT ; 
 int cmd_db_get_header (char const*,struct entry_header const**,int /*<<< orphan*/ *) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

enum cmd_db_hw_type cmd_db_read_slave_id(const char *id)
{
	int ret;
	const struct entry_header *ent;
	u32 addr;

	ret = cmd_db_get_header(id, &ent, NULL);
	if (ret < 0)
		return CMD_DB_HW_INVALID;

	addr = le32_to_cpu(ent->addr);
	return (addr >> SLAVE_ID_SHIFT) & SLAVE_ID_MASK;
}