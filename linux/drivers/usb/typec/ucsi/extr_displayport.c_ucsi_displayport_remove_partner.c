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
struct TYPE_2__ {scalar_t__ status; scalar_t__ conf; } ;
struct ucsi_dp {int initialized; TYPE_1__ data; } ;
struct typec_altmode {int dummy; } ;

/* Variables and functions */
 struct ucsi_dp* typec_altmode_get_drvdata (struct typec_altmode*) ; 

void ucsi_displayport_remove_partner(struct typec_altmode *alt)
{
	struct ucsi_dp *dp;

	if (!alt)
		return;

	dp = typec_altmode_get_drvdata(alt);
	dp->data.conf = 0;
	dp->data.status = 0;
	dp->initialized = false;
}