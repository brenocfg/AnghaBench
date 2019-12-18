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
struct mtd_info {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  directory ; 
 struct device_node* mtd_get_of_node (struct mtd_info*) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void parse_redboot_of(struct mtd_info *master)
{
	struct device_node *np;
	u32 dirblock;
	int ret;

	np = mtd_get_of_node(master);
	if (!np)
		return;

	ret = of_property_read_u32(np, "fis-index-block", &dirblock);
	if (ret)
		return;

	/*
	 * Assign the block found in the device tree to the local
	 * directory block pointer.
	 */
	directory = dirblock;
}