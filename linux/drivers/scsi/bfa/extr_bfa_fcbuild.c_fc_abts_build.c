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
typedef  void* u32 ;
typedef  int u16 ;
struct fchs_s {int /*<<< orphan*/  ox_id; void* s_id; void* d_id; int /*<<< orphan*/  cat_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_CAT_ABTS ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  fc_bls_req_tmpl ; 
 int /*<<< orphan*/  memcpy (struct fchs_s*,int /*<<< orphan*/ *,int) ; 

u16
fc_abts_build(struct fchs_s *fchs, u32 d_id, u32 s_id, u16 ox_id)
{
	memcpy(fchs, &fc_bls_req_tmpl, sizeof(struct fchs_s));
	fchs->cat_info = FC_CAT_ABTS;
	fchs->d_id = (d_id);
	fchs->s_id = (s_id);
	fchs->ox_id = cpu_to_be16(ox_id);

	return sizeof(struct fchs_s);
}