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
struct host1x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  host1x_intr_stop (struct host1x*) ; 

void host1x_intr_deinit(struct host1x *host)
{
	host1x_intr_stop(host);
}