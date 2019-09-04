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
typedef  void* u64 ;
typedef  enum ps3_spu_resource_type { ____Placeholder_ps3_spu_resource_type } ps3_spu_resource_type ;

/* Variables and functions */
 int /*<<< orphan*/  PS3_LPAR_ID_CURRENT ; 
 int /*<<< orphan*/  make_field (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_first_field (char*,int /*<<< orphan*/ ) ; 
 int read_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,void**,void**) ; 

int ps3_repository_read_spu_resource_id(unsigned int res_index,
	enum ps3_spu_resource_type *resource_type, unsigned int *resource_id)
{
	int result;
	u64 v1 = 0;
	u64 v2 = 0;

	result = read_node(PS3_LPAR_ID_CURRENT,
		make_first_field("bi", 0),
		make_field("spursv", 0),
		res_index,
		0,
		&v1, &v2);
	*resource_type = v1;
	*resource_id = v2;
	return result;
}