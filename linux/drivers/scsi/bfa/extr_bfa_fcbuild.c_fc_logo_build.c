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
typedef  int /*<<< orphan*/  wwn_t ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct fchs_s {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  els_code; } ;
struct fc_logo_s {int /*<<< orphan*/  orig_port_name; int /*<<< orphan*/  nport_id; TYPE_1__ els_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_ELS_LOGO ; 
 int /*<<< orphan*/  fc_els_req_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct fc_logo_s*,char,int) ; 

u16
fc_logo_build(struct fchs_s *fchs, struct fc_logo_s *logo, u32 d_id, u32 s_id,
	      u16 ox_id, wwn_t port_name)
{
	fc_els_req_build(fchs, d_id, s_id, ox_id);

	memset(logo, '\0', sizeof(struct fc_logo_s));
	logo->els_cmd.els_code = FC_ELS_LOGO;
	logo->nport_id = (s_id);
	logo->orig_port_name = port_name;

	return sizeof(struct fc_logo_s);
}