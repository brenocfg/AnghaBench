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
struct sfp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SFP_E_DEV_UP ; 
 int /*<<< orphan*/  sfp_sm_event (struct sfp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sfp_start(struct sfp *sfp)
{
	sfp_sm_event(sfp, SFP_E_DEV_UP);
}