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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fchs_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_ELS_PLOGI ; 
 int /*<<< orphan*/  fc_plogi_x_build (struct fchs_s*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u16
fc_plogi_build(struct fchs_s *fchs, void *pld, u32 d_id, u32 s_id,
	       u16 ox_id, wwn_t port_name, wwn_t node_name,
	       u16 pdu_size, u16 bb_cr)
{
	return fc_plogi_x_build(fchs, pld, d_id, s_id, ox_id, port_name,
				node_name, pdu_size, bb_cr, FC_ELS_PLOGI);
}