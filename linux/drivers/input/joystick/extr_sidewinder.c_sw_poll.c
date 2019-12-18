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
struct sw {int /*<<< orphan*/  bads; int /*<<< orphan*/  reads; } ;
struct gameport {int dummy; } ;

/* Variables and functions */
 struct sw* gameport_get_drvdata (struct gameport*) ; 
 scalar_t__ sw_read (struct sw*) ; 

__attribute__((used)) static void sw_poll(struct gameport *gameport)
{
	struct sw *sw = gameport_get_drvdata(gameport);

	sw->reads++;
	if (sw_read(sw))
		sw->bads++;
}