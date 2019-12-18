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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct ast_vhub_ep {TYPE_1__ ep0; } ;
struct ast_vhub_dev {struct ast_vhub_ep ep0; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ast_vhub_nuke (struct ast_vhub_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep0_state_token ; 

void ast_vhub_reset_ep0(struct ast_vhub_dev *dev)
{
	struct ast_vhub_ep *ep = &dev->ep0;

	ast_vhub_nuke(ep, -EIO);
	ep->ep0.state = ep0_state_token;
}