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
 int /*<<< orphan*/  ntb_clear_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_link_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pp_clear_ctx(struct pp_ctx *pp)
{
	ntb_link_disable(pp->ntb);

	ntb_clear_ctx(pp->ntb);
}