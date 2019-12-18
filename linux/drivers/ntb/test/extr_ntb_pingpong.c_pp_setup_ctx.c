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
struct pp_ctx {int /*<<< orphan*/  ntb; } ;

/* Variables and functions */
 int /*<<< orphan*/  NTB_SPEED_AUTO ; 
 int /*<<< orphan*/  NTB_WIDTH_AUTO ; 
 int /*<<< orphan*/  ntb_link_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_link_event (int /*<<< orphan*/ ) ; 
 int ntb_set_ctx (int /*<<< orphan*/ ,struct pp_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_ops ; 

__attribute__((used)) static int pp_setup_ctx(struct pp_ctx *pp)
{
	int ret;

	ret = ntb_set_ctx(pp->ntb, pp, &pp_ops);
	if (ret)
		return ret;

	ntb_link_enable(pp->ntb, NTB_SPEED_AUTO, NTB_WIDTH_AUTO);
	/* Might be not necessary */
	ntb_link_event(pp->ntb);

	return 0;
}