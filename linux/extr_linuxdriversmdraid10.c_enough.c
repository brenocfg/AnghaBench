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
struct r10conf {int dummy; } ;

/* Variables and functions */
 scalar_t__ _enough (struct r10conf*,int,int) ; 

__attribute__((used)) static int enough(struct r10conf *conf, int ignore)
{
	/* when calling 'enough', both 'prev' and 'geo' must
	 * be stable.
	 * This is ensured if ->reconfig_mutex or ->device_lock
	 * is held.
	 */
	return _enough(conf, 0, ignore) &&
		_enough(conf, 1, ignore);
}