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
 int /*<<< orphan*/  PS3_LPAR_ID_CURRENT ; 
 int /*<<< orphan*/  make_field (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_first_field (char*,int /*<<< orphan*/ ) ; 
 int read_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ps3_repository_read_rm_size(unsigned int ppe_id, u64 *rm_size)
{
	return read_node(PS3_LPAR_ID_CURRENT,
		make_first_field("bi", 0),
		make_field("pu", 0),
		ppe_id,
		make_field("rm_size", 0),
		rm_size, NULL);
}