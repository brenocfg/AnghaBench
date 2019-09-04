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
struct mei_device {scalar_t__ pg_event; } ;

/* Variables and functions */
 scalar_t__ MEI_PG_EVENT_INTR_WAIT ; 
 scalar_t__ MEI_PG_EVENT_WAIT ; 

__attribute__((used)) static bool mei_me_pg_in_transition(struct mei_device *dev)
{
	return dev->pg_event >= MEI_PG_EVENT_WAIT &&
	       dev->pg_event <= MEI_PG_EVENT_INTR_WAIT;
}