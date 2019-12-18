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
struct sfp {int /*<<< orphan*/  sfp_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  SFP_S_LINK_UP ; 
 int /*<<< orphan*/  sfp_link_up (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfp_sm_next (struct sfp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sfp_sm_link_up(struct sfp *sfp)
{
	sfp_link_up(sfp->sfp_bus);
	sfp_sm_next(sfp, SFP_S_LINK_UP, 0);
}