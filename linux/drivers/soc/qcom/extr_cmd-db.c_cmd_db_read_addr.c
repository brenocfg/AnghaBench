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
typedef  int /*<<< orphan*/  u32 ;
struct entry_header {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int cmd_db_get_header (char const*,struct entry_header const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

u32 cmd_db_read_addr(const char *id)
{
	int ret;
	const struct entry_header *ent;

	ret = cmd_db_get_header(id, &ent, NULL);

	return ret < 0 ? 0 : le32_to_cpu(ent->addr);
}