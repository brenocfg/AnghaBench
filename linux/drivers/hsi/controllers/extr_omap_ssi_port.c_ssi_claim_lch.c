#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct omap_ssi_controller {TYPE_1__* gdd_trn; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct hsi_port {TYPE_3__ device; } ;
struct TYPE_5__ {int /*<<< orphan*/  sgl; } ;
struct hsi_msg {TYPE_2__ sgt; int /*<<< orphan*/  cl; } ;
struct hsi_controller {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sg; struct hsi_msg* msg; } ;

/* Variables and functions */
 int EBUSY ; 
 int SSI_MAX_GDD_LCH ; 
 struct omap_ssi_controller* hsi_controller_drvdata (struct hsi_controller*) ; 
 struct hsi_port* hsi_get_port (int /*<<< orphan*/ ) ; 
 struct hsi_controller* to_hsi_controller (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssi_claim_lch(struct hsi_msg *msg)
{

	struct hsi_port *port = hsi_get_port(msg->cl);
	struct hsi_controller *ssi = to_hsi_controller(port->device.parent);
	struct omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	int lch;

	for (lch = 0; lch < SSI_MAX_GDD_LCH; lch++)
		if (!omap_ssi->gdd_trn[lch].msg) {
			omap_ssi->gdd_trn[lch].msg = msg;
			omap_ssi->gdd_trn[lch].sg = msg->sgt.sgl;
			return lch;
		}

	return -EBUSY;
}