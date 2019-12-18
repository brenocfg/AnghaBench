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
typedef  int /*<<< orphan*/  wwn_t ;
typedef  int /*<<< orphan*/  u16 ;
struct bfa_fcs_vport_s {int dummy; } ;
struct bfa_fcs_s {int dummy; } ;
struct bfa_fcs_fabric_s {int dummy; } ;

/* Variables and functions */
 struct bfa_fcs_vport_s* bfa_fcs_fabric_vport_lookup (struct bfa_fcs_fabric_s*,int /*<<< orphan*/ ) ; 
 struct bfa_fcs_fabric_s* bfa_fcs_vf_lookup (struct bfa_fcs_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_fcs_s*,int /*<<< orphan*/ ) ; 

struct bfa_fcs_vport_s *
bfa_fcs_vport_lookup(struct bfa_fcs_s *fcs, u16 vf_id, wwn_t vpwwn)
{
	struct bfa_fcs_vport_s *vport;
	struct bfa_fcs_fabric_s *fabric;

	bfa_trc(fcs, vf_id);
	bfa_trc(fcs, vpwwn);

	fabric = bfa_fcs_vf_lookup(fcs, vf_id);
	if (!fabric) {
		bfa_trc(fcs, vf_id);
		return NULL;
	}

	vport = bfa_fcs_fabric_vport_lookup(fabric, vpwwn);
	return vport;
}