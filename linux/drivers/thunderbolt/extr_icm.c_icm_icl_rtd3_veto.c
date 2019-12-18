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
struct tb {int dummy; } ;
struct icm_pkg_header {int dummy; } ;
struct icm_icl_event_rtd3_veto {scalar_t__ veto_reason; } ;

/* Variables and functions */
 int /*<<< orphan*/  icm_veto_begin (struct tb*) ; 
 int /*<<< orphan*/  icm_veto_end (struct tb*) ; 
 int /*<<< orphan*/  tb_dbg (struct tb*,char*,scalar_t__) ; 

__attribute__((used)) static void icm_icl_rtd3_veto(struct tb *tb, const struct icm_pkg_header *hdr)
{
	const struct icm_icl_event_rtd3_veto *pkg =
		(const struct icm_icl_event_rtd3_veto *)hdr;

	tb_dbg(tb, "ICM rtd3 veto=0x%08x\n", pkg->veto_reason);

	if (pkg->veto_reason)
		icm_veto_begin(tb);
	else
		icm_veto_end(tb);
}