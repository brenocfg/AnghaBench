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
typedef  int u16 ;
struct fchs_s {int dummy; } ;
struct fc_rscn_pl_s {int pagelen; TYPE_1__* event; int /*<<< orphan*/  payldlen; int /*<<< orphan*/  command; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_ELS_RSCN ; 
 int /*<<< orphan*/  FC_FABRIC_CONTROLLER ; 
 int /*<<< orphan*/  FC_RSCN_FORMAT_PORTID ; 
 int /*<<< orphan*/  bfa_hton3b (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  fc_els_req_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

u16
fc_rscn_build(struct fchs_s *fchs, struct fc_rscn_pl_s *rscn,
		u32 s_id, u16 ox_id)
{
	u32        d_id = bfa_hton3b(FC_FABRIC_CONTROLLER);
	u16        payldlen;

	fc_els_req_build(fchs, d_id, s_id, ox_id);
	rscn->command = FC_ELS_RSCN;
	rscn->pagelen = sizeof(rscn->event[0]);

	payldlen = sizeof(u32) + rscn->pagelen;
	rscn->payldlen = cpu_to_be16(payldlen);

	rscn->event[0].format = FC_RSCN_FORMAT_PORTID;
	rscn->event[0].portid = s_id;

	return sizeof(struct fc_rscn_pl_s);
}