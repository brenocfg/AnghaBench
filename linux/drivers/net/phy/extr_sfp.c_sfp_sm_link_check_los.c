#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int options; } ;
struct TYPE_4__ {TYPE_1__ ext; } ;
struct sfp {unsigned int state; TYPE_2__ id; } ;

/* Variables and functions */
 unsigned int SFP_F_LOS ; 
 int /*<<< orphan*/  SFP_OPTIONS_LOS_INVERTED ; 
 int /*<<< orphan*/  SFP_OPTIONS_LOS_NORMAL ; 
 int /*<<< orphan*/  SFP_S_WAIT_LOS ; 
 int cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfp_sm_link_up (struct sfp*) ; 
 int /*<<< orphan*/  sfp_sm_next (struct sfp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sfp_sm_link_check_los(struct sfp *sfp)
{
	unsigned int los = sfp->state & SFP_F_LOS;

	/* If neither SFP_OPTIONS_LOS_INVERTED nor SFP_OPTIONS_LOS_NORMAL
	 * are set, we assume that no LOS signal is available.
	 */
	if (sfp->id.ext.options & cpu_to_be16(SFP_OPTIONS_LOS_INVERTED))
		los ^= SFP_F_LOS;
	else if (!(sfp->id.ext.options & cpu_to_be16(SFP_OPTIONS_LOS_NORMAL)))
		los = 0;

	if (los)
		sfp_sm_next(sfp, SFP_S_WAIT_LOS, 0);
	else
		sfp_sm_link_up(sfp);
}