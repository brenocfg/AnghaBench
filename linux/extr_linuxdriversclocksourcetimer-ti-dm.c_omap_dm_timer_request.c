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
struct omap_dm_timer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQUEST_ANY ; 
 struct omap_dm_timer* _omap_dm_timer_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct omap_dm_timer *omap_dm_timer_request(void)
{
	return _omap_dm_timer_request(REQUEST_ANY, NULL);
}