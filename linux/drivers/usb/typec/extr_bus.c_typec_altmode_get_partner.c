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
struct typec_altmode {int dummy; } ;
struct TYPE_4__ {TYPE_1__* partner; } ;
struct TYPE_3__ {struct typec_altmode const adev; } ;

/* Variables and functions */
 TYPE_2__* to_altmode (struct typec_altmode*) ; 

const struct typec_altmode *
typec_altmode_get_partner(struct typec_altmode *adev)
{
	return adev ? &to_altmode(adev)->partner->adev : NULL;
}