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
struct subchannel_id {int /*<<< orphan*/  sch_no; int /*<<< orphan*/  ssid; } ;
struct idset {int dummy; } ;

/* Variables and functions */
 int idset_contains (struct idset*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int idset_sch_contains(struct idset *set, struct subchannel_id schid)
{
	return idset_contains(set, schid.ssid, schid.sch_no);
}