#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nasid_t ;
struct TYPE_7__ {int /*<<< orphan*/  brd_nasid; } ;
typedef  TYPE_2__ lboard_t ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  physid; } ;
struct TYPE_8__ {TYPE_1__ hub_info; } ;
typedef  TYPE_3__ klhub_t ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_NASID ; 
 int KLINFO_ENABLE ; 
 int /*<<< orphan*/  KLSTRUCT_HUB ; 
 scalar_t__ find_first_component (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static nasid_t get_actual_nasid(lboard_t *brd)
{
	klhub_t *hub;

	if (!brd)
		return INVALID_NASID;

	/* find out if we are a completely disabled brd. */
	hub  = (klhub_t *)find_first_component(brd, KLSTRUCT_HUB);
	if (!hub)
		return INVALID_NASID;
	if (!(hub->hub_info.flags & KLINFO_ENABLE))	/* disabled node brd */
		return hub->hub_info.physid;
	else
		return brd->brd_nasid;
}