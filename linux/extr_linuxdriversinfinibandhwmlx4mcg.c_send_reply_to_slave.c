#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct ib_sa_mcmember_data {int scope_join_state; int /*<<< orphan*/  port_gid; } ;
struct mcast_group {int /*<<< orphan*/  demux; TYPE_3__* func; struct ib_sa_mcmember_data rec; } ;
struct TYPE_5__ {scalar_t__ comp_mask; void* attr_offset; int /*<<< orphan*/  sm_key; } ;
struct TYPE_4__ {int base_version; int class_version; int /*<<< orphan*/  attr_mod; void* attr_id; int /*<<< orphan*/  tid; void* class_specific; void* status; int /*<<< orphan*/  method; int /*<<< orphan*/  mgmt_class; } ;
struct ib_sa_mad {TYPE_2__ sa_hdr; TYPE_1__ mad_hdr; int /*<<< orphan*/  data; } ;
struct ib_mad {int dummy; } ;
struct TYPE_6__ {int join_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_MGMT_CLASS_SUBN_ADM ; 
 int /*<<< orphan*/  IB_MGMT_METHOD_GET_RESP ; 
 int IB_SA_ATTR_MC_MEMBER_REC ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct ib_sa_mad*,int /*<<< orphan*/ ,int) ; 
 int send_mad_to_slave (int,int /*<<< orphan*/ ,struct ib_mad*) ; 

__attribute__((used)) static int send_reply_to_slave(int slave, struct mcast_group *group,
		struct ib_sa_mad *req_sa_mad, u16 status)
{
	struct ib_sa_mad mad;
	struct ib_sa_mcmember_data *sa_data = (struct ib_sa_mcmember_data *)&mad.data;
	struct ib_sa_mcmember_data *req_sa_data = (struct ib_sa_mcmember_data *)&req_sa_mad->data;
	int ret;

	memset(&mad, 0, sizeof mad);
	mad.mad_hdr.base_version = 1;
	mad.mad_hdr.mgmt_class = IB_MGMT_CLASS_SUBN_ADM;
	mad.mad_hdr.class_version = 2;
	mad.mad_hdr.method = IB_MGMT_METHOD_GET_RESP;
	mad.mad_hdr.status = cpu_to_be16(status);
	mad.mad_hdr.class_specific = cpu_to_be16(0);
	mad.mad_hdr.tid = req_sa_mad->mad_hdr.tid;
	*(u8 *)&mad.mad_hdr.tid = 0; /* resetting tid to 0 */
	mad.mad_hdr.attr_id = cpu_to_be16(IB_SA_ATTR_MC_MEMBER_REC);
	mad.mad_hdr.attr_mod = cpu_to_be32(0);
	mad.sa_hdr.sm_key = req_sa_mad->sa_hdr.sm_key;
	mad.sa_hdr.attr_offset = cpu_to_be16(7);
	mad.sa_hdr.comp_mask = 0; /* ignored on responses, see IBTA spec */

	*sa_data = group->rec;

	/* reconstruct VF's requested join_state and port_gid */
	sa_data->scope_join_state &= 0xf0;
	sa_data->scope_join_state |= (group->func[slave].join_state & 0x0f);
	memcpy(&sa_data->port_gid, &req_sa_data->port_gid, sizeof req_sa_data->port_gid);

	ret = send_mad_to_slave(slave, group->demux, (struct ib_mad *)&mad);
	return ret;
}