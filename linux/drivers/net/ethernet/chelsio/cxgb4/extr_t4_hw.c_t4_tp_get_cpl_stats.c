#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tp_cpl_stats {int /*<<< orphan*/  rsp; int /*<<< orphan*/  req; } ;
struct TYPE_3__ {int nchan; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  TP_MIB_CPL_IN_REQ_0_A ; 
 int /*<<< orphan*/  TP_MIB_CPL_OUT_RSP_0_A ; 
 int /*<<< orphan*/  t4_tp_mib_read (struct adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

void t4_tp_get_cpl_stats(struct adapter *adap, struct tp_cpl_stats *st,
			 bool sleep_ok)
{
	int nchan = adap->params.arch.nchan;

	t4_tp_mib_read(adap, st->req, nchan, TP_MIB_CPL_IN_REQ_0_A, sleep_ok);

	t4_tp_mib_read(adap, st->rsp, nchan, TP_MIB_CPL_OUT_RSP_0_A, sleep_ok);
}