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
struct iforce {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void iforce_serio_stop_io(struct iforce *iforce)
{
	//TODO: Wait for the last packets to be sent
}