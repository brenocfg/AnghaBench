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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  issuer_lid; int /*<<< orphan*/  trap_num; int /*<<< orphan*/  prod_type_lsb; int /*<<< orphan*/  generic_type; } ;
struct trap_node {TYPE_1__ data; int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IB_NOTICE_PROD_CA ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct trap_node* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct trap_node *create_trap_node(u8 type, __be16 trap_num, u32 lid)
{
	struct trap_node *trap;

	trap = kzalloc(sizeof(*trap), GFP_ATOMIC);
	if (!trap)
		return NULL;

	INIT_LIST_HEAD(&trap->list);
	trap->data.generic_type = type;
	trap->data.prod_type_lsb = IB_NOTICE_PROD_CA;
	trap->data.trap_num = trap_num;
	trap->data.issuer_lid = cpu_to_be32(lid);

	return trap;
}