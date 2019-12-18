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
struct rocker_wait {int done; int nowait; } ;

/* Variables and functions */

__attribute__((used)) static void rocker_wait_reset(struct rocker_wait *wait)
{
	wait->done = false;
	wait->nowait = false;
}