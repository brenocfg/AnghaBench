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
struct TYPE_2__ {int /*<<< orphan*/  els_code; } ;
struct fc_rpsc_cmd_s {TYPE_1__ els_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_ELS_RPSC ; 
 int /*<<< orphan*/  fc_els_req_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct fc_rpsc_cmd_s*,int /*<<< orphan*/ ,int) ; 

u16
fc_rpsc_build(struct fchs_s *fchs, struct fc_rpsc_cmd_s *rpsc, u32 d_id,
		u32 s_id, u16 ox_id)
{
	fc_els_req_build(fchs, d_id, s_id, ox_id);

	memset(rpsc, 0, sizeof(struct fc_rpsc_cmd_s));

	rpsc->els_cmd.els_code = FC_ELS_RPSC;
	return sizeof(struct fc_rpsc_cmd_s);
}