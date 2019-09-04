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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct send_context {scalar_t__ type; int /*<<< orphan*/  hw_context; struct hfi1_devdata* dd; } ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_STATIC_RATE_CONTROL_SMASK (int /*<<< orphan*/ ) ; 
 scalar_t__ HFI1_CAP_IS_KSET (int /*<<< orphan*/ ) ; 
 scalar_t__ HFI1_CAP_IS_USET (int /*<<< orphan*/ ) ; 
 scalar_t__ SC_USER ; 
 int /*<<< orphan*/  SEND_CTXT_CHECK_ENABLE ; 
 int /*<<< orphan*/  SET_STATIC_RATE_CONTROL_SMASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATIC_RATE_CTRL ; 
 int /*<<< orphan*/  read_kctxt_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_kctxt_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hfi1_init_ctxt(struct send_context *sc)
{
	if (sc) {
		struct hfi1_devdata *dd = sc->dd;
		u64 reg;
		u8 set = (sc->type == SC_USER ?
			  HFI1_CAP_IS_USET(STATIC_RATE_CTRL) :
			  HFI1_CAP_IS_KSET(STATIC_RATE_CTRL));
		reg = read_kctxt_csr(dd, sc->hw_context,
				     SEND_CTXT_CHECK_ENABLE);
		if (set)
			CLEAR_STATIC_RATE_CONTROL_SMASK(reg);
		else
			SET_STATIC_RATE_CONTROL_SMASK(reg);
		write_kctxt_csr(dd, sc->hw_context,
				SEND_CTXT_CHECK_ENABLE, reg);
	}
}