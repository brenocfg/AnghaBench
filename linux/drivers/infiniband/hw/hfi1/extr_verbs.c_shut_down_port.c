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
typedef  int u8 ;
struct rvt_dev_info {int dummy; } ;
struct hfi1_pportdata {int dummy; } ;
struct hfi1_ibdev {int dummy; } ;
struct hfi1_devdata {struct hfi1_pportdata* pport; } ;

/* Variables and functions */
 int /*<<< orphan*/  HLS_DN_DOWNDEF ; 
 int /*<<< orphan*/  OPA_LINKDOWN_REASON_UNKNOWN ; 
 struct hfi1_devdata* dd_from_dev (struct hfi1_ibdev*) ; 
 struct hfi1_ibdev* dev_from_rdi (struct rvt_dev_info*) ; 
 int /*<<< orphan*/  set_link_down_reason (struct hfi1_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int set_link_state (struct hfi1_pportdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int shut_down_port(struct rvt_dev_info *rdi, u8 port_num)
{
	struct hfi1_ibdev *verbs_dev = dev_from_rdi(rdi);
	struct hfi1_devdata *dd = dd_from_dev(verbs_dev);
	struct hfi1_pportdata *ppd = &dd->pport[port_num - 1];
	int ret;

	set_link_down_reason(ppd, OPA_LINKDOWN_REASON_UNKNOWN, 0,
			     OPA_LINKDOWN_REASON_UNKNOWN);
	ret = set_link_state(ppd, HLS_DN_DOWNDEF);
	return ret;
}