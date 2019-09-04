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
struct mvpp2_port {struct mvpp2* priv; int /*<<< orphan*/  id; } ;
struct mvpp2 {TYPE_1__* prs_shadow; } ;
struct TYPE_2__ {int valid; } ;

/* Variables and functions */
 unsigned int MVPP2_PRS_VID_PORT_DFLT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_prs_hw_inv (struct mvpp2*,unsigned int) ; 

void mvpp2_prs_vid_disable_filtering(struct mvpp2_port *port)
{
	unsigned int tid = MVPP2_PRS_VID_PORT_DFLT(port->id);
	struct mvpp2 *priv = port->priv;

	/* Invalidate the guard entry */
	mvpp2_prs_hw_inv(priv, tid);

	priv->prs_shadow[tid].valid = false;
}