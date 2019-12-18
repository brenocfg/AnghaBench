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
typedef  int u32 ;
struct tg3 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_PROCESSED ; 
 int /*<<< orphan*/  HOSTCC_FLOW_ATTN ; 
 int HOSTCC_FLOW_ATTN_MBUF_LWM ; 
 int /*<<< orphan*/  MSGINT_STATUS ; 
 int MSGINT_STATUS_MSI_REQ ; 
 int /*<<< orphan*/  RDMAC_STATUS ; 
 int /*<<< orphan*/  WDMAC_STATUS ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tg3_dump_state (struct tg3*) ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_flag_set (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_reset_task_schedule (struct tg3*) ; 
 int tr32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_process_error(struct tg3 *tp)
{
	u32 val;
	bool real_error = false;

	if (tg3_flag(tp, ERROR_PROCESSED))
		return;

	/* Check Flow Attention register */
	val = tr32(HOSTCC_FLOW_ATTN);
	if (val & ~HOSTCC_FLOW_ATTN_MBUF_LWM) {
		netdev_err(tp->dev, "FLOW Attention error.  Resetting chip.\n");
		real_error = true;
	}

	if (tr32(MSGINT_STATUS) & ~MSGINT_STATUS_MSI_REQ) {
		netdev_err(tp->dev, "MSI Status error.  Resetting chip.\n");
		real_error = true;
	}

	if (tr32(RDMAC_STATUS) || tr32(WDMAC_STATUS)) {
		netdev_err(tp->dev, "DMA Status error.  Resetting chip.\n");
		real_error = true;
	}

	if (!real_error)
		return;

	tg3_dump_state(tp);

	tg3_flag_set(tp, ERROR_PROCESSED);
	tg3_reset_task_schedule(tp);
}