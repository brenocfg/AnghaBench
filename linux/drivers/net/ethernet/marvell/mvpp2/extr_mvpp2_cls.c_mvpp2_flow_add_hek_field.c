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
struct mvpp2_cls_flow_entry {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MVPP2_FLOW_N_FIELDS ; 
 int mvpp2_cls_flow_hek_num_get (struct mvpp2_cls_flow_entry*) ; 
 int /*<<< orphan*/  mvpp2_cls_flow_hek_num_set (struct mvpp2_cls_flow_entry*,int) ; 
 int /*<<< orphan*/  mvpp2_cls_flow_hek_set (struct mvpp2_cls_flow_entry*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvpp2_flow_add_hek_field(struct mvpp2_cls_flow_entry *fe,
				    u32 field_id)
{
	int nb_fields = mvpp2_cls_flow_hek_num_get(fe);

	if (nb_fields == MVPP2_FLOW_N_FIELDS)
		return -EINVAL;

	mvpp2_cls_flow_hek_set(fe, nb_fields, field_id);

	mvpp2_cls_flow_hek_num_set(fe, nb_fields + 1);

	return 0;
}