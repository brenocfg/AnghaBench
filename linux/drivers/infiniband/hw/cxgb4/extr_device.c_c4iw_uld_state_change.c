#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pdev; } ;
struct uld_ctx {TYPE_2__* dev; TYPE_3__ lldi; int /*<<< orphan*/  reg_work; } ;
struct ib_event {int /*<<< orphan*/ * device; int /*<<< orphan*/  event; } ;
typedef  enum cxgb4_state { ____Placeholder_cxgb4_state } cxgb4_state ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  ibdev; TYPE_1__ rdev; } ;

/* Variables and functions */
#define  CXGB4_STATE_DETACH 132 
#define  CXGB4_STATE_DOWN 131 
#define  CXGB4_STATE_FATAL_ERROR 130 
#define  CXGB4_STATE_START_RECOVERY 129 
#define  CXGB4_STATE_UP 128 
 int /*<<< orphan*/  IB_EVENT_DEVICE_FATAL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  T4_FATAL_ERROR ; 
 TYPE_2__* c4iw_alloc (TYPE_3__*) ; 
 int /*<<< orphan*/  c4iw_register_device ; 
 int /*<<< orphan*/  c4iw_remove (struct uld_ctx*) ; 
 int /*<<< orphan*/  ib_dispatch_event (struct ib_event*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reg_workq ; 

__attribute__((used)) static int c4iw_uld_state_change(void *handle, enum cxgb4_state new_state)
{
	struct uld_ctx *ctx = handle;

	pr_debug("new_state %u\n", new_state);
	switch (new_state) {
	case CXGB4_STATE_UP:
		pr_info("%s: Up\n", pci_name(ctx->lldi.pdev));
		if (!ctx->dev) {
			ctx->dev = c4iw_alloc(&ctx->lldi);
			if (IS_ERR(ctx->dev)) {
				pr_err("%s: initialization failed: %ld\n",
				       pci_name(ctx->lldi.pdev),
				       PTR_ERR(ctx->dev));
				ctx->dev = NULL;
				break;
			}

			INIT_WORK(&ctx->reg_work, c4iw_register_device);
			queue_work(reg_workq, &ctx->reg_work);
		}
		break;
	case CXGB4_STATE_DOWN:
		pr_info("%s: Down\n", pci_name(ctx->lldi.pdev));
		if (ctx->dev)
			c4iw_remove(ctx);
		break;
	case CXGB4_STATE_FATAL_ERROR:
	case CXGB4_STATE_START_RECOVERY:
		pr_info("%s: Fatal Error\n", pci_name(ctx->lldi.pdev));
		if (ctx->dev) {
			struct ib_event event = {};

			ctx->dev->rdev.flags |= T4_FATAL_ERROR;
			event.event  = IB_EVENT_DEVICE_FATAL;
			event.device = &ctx->dev->ibdev;
			ib_dispatch_event(&event);
			c4iw_remove(ctx);
		}
		break;
	case CXGB4_STATE_DETACH:
		pr_info("%s: Detach\n", pci_name(ctx->lldi.pdev));
		if (ctx->dev)
			c4iw_remove(ctx);
		break;
	}
	return 0;
}