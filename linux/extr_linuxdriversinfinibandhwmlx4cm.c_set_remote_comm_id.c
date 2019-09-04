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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ attr_id; } ;
struct ib_mad {TYPE_1__ mad_hdr; } ;
struct cm_sidr_generic_msg {void* request_id; } ;
struct cm_generic_msg {void* remote_comm_id; } ;

/* Variables and functions */
 scalar_t__ CM_SIDR_REP_ATTR_ID ; 
 scalar_t__ CM_SIDR_REQ_ATTR_ID ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void set_remote_comm_id(struct ib_mad *mad, u32 cm_id)
{
	if (mad->mad_hdr.attr_id == CM_SIDR_REP_ATTR_ID) {
		struct cm_sidr_generic_msg *msg =
			(struct cm_sidr_generic_msg *)mad;
		msg->request_id = cpu_to_be32(cm_id);
	} else if (mad->mad_hdr.attr_id == CM_SIDR_REQ_ATTR_ID) {
		pr_err("trying to set remote_comm_id in SIDR_REQ\n");
		return;
	} else {
		struct cm_generic_msg *msg = (struct cm_generic_msg *)mad;
		msg->remote_comm_id = cpu_to_be32(cm_id);
	}
}