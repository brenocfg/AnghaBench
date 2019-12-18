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
struct vchiq_state {int unused_service; struct vchiq_service** services; } ;
struct TYPE_2__ {int /*<<< orphan*/  fourcc; } ;
struct vchiq_service {scalar_t__ srvstate; scalar_t__ service_use_count; int /*<<< orphan*/  client_id; TYPE_1__ base; } ;
struct vchiq_arm_state {int vc_suspend_state; int vc_resume_state; int peer_use_count; int videocore_use_count; int /*<<< orphan*/  susp_res_lock; } ;
struct service_data_struct {scalar_t__ use_count; int /*<<< orphan*/  clientid; int /*<<< orphan*/  fourcc; } ;
typedef  enum vc_suspend_status { ____Placeholder_vc_suspend_status } vc_suspend_status ;
typedef  enum vc_resume_status { ____Placeholder_vc_resume_status } vc_resume_status ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_SERVICES ; 
 int /*<<< orphan*/  VCHIQ_FOURCC_AS_4CHARS (int /*<<< orphan*/ ) ; 
 scalar_t__ VCHIQ_SRVSTATE_FREE ; 
 int VC_RESUME_NUM_OFFSET ; 
 int VC_SUSPEND_NUM_OFFSET ; 
 int /*<<< orphan*/  kfree (struct service_data_struct*) ; 
 struct service_data_struct* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int* resume_state_names ; 
 int* suspend_state_names ; 
 int /*<<< orphan*/  vchiq_dump_platform_use_state (struct vchiq_state*) ; 
 int /*<<< orphan*/  vchiq_log_warning (int /*<<< orphan*/ ,char*,int,...) ; 
 struct vchiq_arm_state* vchiq_platform_get_arm_state (struct vchiq_state*) ; 
 int /*<<< orphan*/  vchiq_susp_log_level ; 

void
vchiq_dump_service_use_state(struct vchiq_state *state)
{
	struct vchiq_arm_state *arm_state = vchiq_platform_get_arm_state(state);
	struct service_data_struct *service_data;
	int i, found = 0;
	/* If there's more than 64 services, only dump ones with
	 * non-zero counts */
	int only_nonzero = 0;
	static const char *nz = "<-- preventing suspend";

	enum vc_suspend_status vc_suspend_state;
	enum vc_resume_status  vc_resume_state;
	int peer_count;
	int vc_use_count;
	int active_services;

	if (!arm_state)
		return;

	service_data = kmalloc_array(MAX_SERVICES, sizeof(*service_data),
				     GFP_KERNEL);
	if (!service_data)
		return;

	read_lock_bh(&arm_state->susp_res_lock);
	vc_suspend_state = arm_state->vc_suspend_state;
	vc_resume_state  = arm_state->vc_resume_state;
	peer_count = arm_state->peer_use_count;
	vc_use_count = arm_state->videocore_use_count;
	active_services = state->unused_service;
	if (active_services > MAX_SERVICES)
		only_nonzero = 1;

	for (i = 0; i < active_services; i++) {
		struct vchiq_service *service_ptr = state->services[i];

		if (!service_ptr)
			continue;

		if (only_nonzero && !service_ptr->service_use_count)
			continue;

		if (service_ptr->srvstate == VCHIQ_SRVSTATE_FREE)
			continue;

		service_data[found].fourcc = service_ptr->base.fourcc;
		service_data[found].clientid = service_ptr->client_id;
		service_data[found].use_count = service_ptr->service_use_count;
		found++;
		if (found >= MAX_SERVICES)
			break;
	}

	read_unlock_bh(&arm_state->susp_res_lock);

	vchiq_log_warning(vchiq_susp_log_level,
		"-- Videcore suspend state: %s --",
		suspend_state_names[vc_suspend_state + VC_SUSPEND_NUM_OFFSET]);
	vchiq_log_warning(vchiq_susp_log_level,
		"-- Videcore resume state: %s --",
		resume_state_names[vc_resume_state + VC_RESUME_NUM_OFFSET]);

	if (only_nonzero)
		vchiq_log_warning(vchiq_susp_log_level, "Too many active "
			"services (%d).  Only dumping up to first %d services "
			"with non-zero use-count", active_services, found);

	for (i = 0; i < found; i++) {
		vchiq_log_warning(vchiq_susp_log_level,
			"----- %c%c%c%c:%d service count %d %s",
			VCHIQ_FOURCC_AS_4CHARS(service_data[i].fourcc),
			service_data[i].clientid,
			service_data[i].use_count,
			service_data[i].use_count ? nz : "");
	}
	vchiq_log_warning(vchiq_susp_log_level,
		"----- VCHIQ use count count %d", peer_count);
	vchiq_log_warning(vchiq_susp_log_level,
		"--- Overall vchiq instance use count %d", vc_use_count);

	kfree(service_data);

	vchiq_dump_platform_use_state(state);
}