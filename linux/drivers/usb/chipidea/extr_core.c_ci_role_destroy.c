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
struct ci_hdrc {scalar_t__* roles; scalar_t__ is_otg; } ;

/* Variables and functions */
 size_t CI_ROLE_GADGET ; 
 int /*<<< orphan*/  ci_hdrc_gadget_destroy (struct ci_hdrc*) ; 
 int /*<<< orphan*/  ci_hdrc_host_destroy (struct ci_hdrc*) ; 
 int /*<<< orphan*/  ci_hdrc_otg_destroy (struct ci_hdrc*) ; 

__attribute__((used)) static inline void ci_role_destroy(struct ci_hdrc *ci)
{
	ci_hdrc_gadget_destroy(ci);
	ci_hdrc_host_destroy(ci);
	if (ci->is_otg && ci->roles[CI_ROLE_GADGET])
		ci_hdrc_otg_destroy(ci);
}