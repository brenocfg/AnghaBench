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
struct cphy {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int mv88x201x_reset(struct cphy *cphy, int wait)
{
	/* This can be done through registers.  It is not required since
	 * a full chip reset is used.
	 */
	return 0;
}