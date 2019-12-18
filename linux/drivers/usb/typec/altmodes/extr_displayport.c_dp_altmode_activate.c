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
struct typec_altmode {int dummy; } ;

/* Variables and functions */
 int typec_altmode_enter (struct typec_altmode*) ; 
 int typec_altmode_exit (struct typec_altmode*) ; 

__attribute__((used)) static int dp_altmode_activate(struct typec_altmode *alt, int activate)
{
	return activate ? typec_altmode_enter(alt) : typec_altmode_exit(alt);
}