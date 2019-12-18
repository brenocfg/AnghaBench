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
struct chp_id {int dummy; } ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 TYPE_1__* chpid_to_chp (struct chp_id) ; 

__attribute__((used)) static void set_chp_logically_online(struct chp_id chpid, int onoff)
{
	chpid_to_chp(chpid)->state = onoff;
}