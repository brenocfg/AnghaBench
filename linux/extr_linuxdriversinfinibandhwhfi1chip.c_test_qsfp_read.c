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
typedef  int /*<<< orphan*/  u8 ;
struct hfi1_pportdata {scalar_t__ port_type; TYPE_1__* dd; } ;
struct TYPE_2__ {int /*<<< orphan*/  hfi1_id; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ PORT_TYPE_QSFP ; 
 int one_qsfp_read (struct hfi1_pportdata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qsfp_mod_present (struct hfi1_pportdata*) ; 

__attribute__((used)) static int test_qsfp_read(struct hfi1_pportdata *ppd)
{
	int ret;
	u8 status;

	/*
	 * Report success if not a QSFP or, if it is a QSFP, but the cable is
	 * not present
	 */
	if (ppd->port_type != PORT_TYPE_QSFP || !qsfp_mod_present(ppd))
		return 0;

	/* read byte 2, the status byte */
	ret = one_qsfp_read(ppd, ppd->dd->hfi1_id, 2, &status, 1);
	if (ret < 0)
		return ret;
	if (ret != 1)
		return -EIO;

	return 0; /* success */
}