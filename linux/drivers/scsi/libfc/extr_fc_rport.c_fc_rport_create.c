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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int node_name; int port_name; int /*<<< orphan*/  roles; scalar_t__ port_id; } ;
struct fc_rport_priv {int /*<<< orphan*/  peers; int /*<<< orphan*/  lld_event_callback; int /*<<< orphan*/  event_work; int /*<<< orphan*/  retry_work; int /*<<< orphan*/  maxframe_size; int /*<<< orphan*/  r_a_tov; int /*<<< orphan*/  e_d_tov; int /*<<< orphan*/  flags; int /*<<< orphan*/  event; int /*<<< orphan*/  rp_state; struct fc_lport* local_port; int /*<<< orphan*/  rp_mutex; int /*<<< orphan*/  kref; TYPE_1__ ids; } ;
struct TYPE_6__ {int /*<<< orphan*/  rports; int /*<<< orphan*/  disc_mutex; } ;
struct TYPE_5__ {int /*<<< orphan*/  rport_event_callback; } ;
struct fc_lport {size_t rport_priv_size; TYPE_3__ disc; TYPE_2__ tt; int /*<<< orphan*/  r_a_tov; int /*<<< orphan*/  e_d_tov; } ;

/* Variables and functions */
 scalar_t__ FC_FID_DIR_SERV ; 
 int /*<<< orphan*/  FC_MIN_MAX_PAYLOAD ; 
 int /*<<< orphan*/  FC_RPORT_ROLE_UNKNOWN ; 
 int /*<<< orphan*/  FC_RP_FLAGS_REC_SUPPORTED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPORT_EV_NONE ; 
 int /*<<< orphan*/  RPORT_ST_INIT ; 
 struct fc_rport_priv* fc_rport_lookup (struct fc_lport*,scalar_t__) ; 
 int /*<<< orphan*/  fc_rport_timeout ; 
 int /*<<< orphan*/  fc_rport_work ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct fc_rport_priv* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct fc_rport_priv *fc_rport_create(struct fc_lport *lport, u32 port_id)
{
	struct fc_rport_priv *rdata;
	size_t rport_priv_size = sizeof(*rdata);

	lockdep_assert_held(&lport->disc.disc_mutex);

	rdata = fc_rport_lookup(lport, port_id);
	if (rdata)
		return rdata;

	if (lport->rport_priv_size > 0)
		rport_priv_size = lport->rport_priv_size;
	rdata = kzalloc(rport_priv_size, GFP_KERNEL);
	if (!rdata)
		return NULL;

	rdata->ids.node_name = -1;
	rdata->ids.port_name = -1;
	rdata->ids.port_id = port_id;
	rdata->ids.roles = FC_RPORT_ROLE_UNKNOWN;

	kref_init(&rdata->kref);
	mutex_init(&rdata->rp_mutex);
	rdata->local_port = lport;
	rdata->rp_state = RPORT_ST_INIT;
	rdata->event = RPORT_EV_NONE;
	rdata->flags = FC_RP_FLAGS_REC_SUPPORTED;
	rdata->e_d_tov = lport->e_d_tov;
	rdata->r_a_tov = lport->r_a_tov;
	rdata->maxframe_size = FC_MIN_MAX_PAYLOAD;
	INIT_DELAYED_WORK(&rdata->retry_work, fc_rport_timeout);
	INIT_WORK(&rdata->event_work, fc_rport_work);
	if (port_id != FC_FID_DIR_SERV) {
		rdata->lld_event_callback = lport->tt.rport_event_callback;
		list_add_rcu(&rdata->peers, &lport->disc.rports);
	}
	return rdata;
}