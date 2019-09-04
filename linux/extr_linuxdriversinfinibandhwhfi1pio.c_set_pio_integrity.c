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
typedef  int /*<<< orphan*/  u32 ;
struct send_context {int type; int /*<<< orphan*/  hw_context; struct hfi1_devdata* dd; } ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ENABLE ; 
 int /*<<< orphan*/  SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_pkt_default_send_ctxt_mask (struct hfi1_devdata*,int) ; 
 int /*<<< orphan*/  write_kctxt_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void set_pio_integrity(struct send_context *sc)
{
	struct hfi1_devdata *dd = sc->dd;
	u32 hw_context = sc->hw_context;
	int type = sc->type;

	write_kctxt_csr(dd, hw_context,
			SC(CHECK_ENABLE),
			hfi1_pkt_default_send_ctxt_mask(dd, type));
}