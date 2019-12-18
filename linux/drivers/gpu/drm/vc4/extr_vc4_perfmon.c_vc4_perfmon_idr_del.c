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
struct vc4_perfmon {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vc4_perfmon_put (struct vc4_perfmon*) ; 

__attribute__((used)) static int vc4_perfmon_idr_del(int id, void *elem, void *data)
{
	struct vc4_perfmon *perfmon = elem;

	vc4_perfmon_put(perfmon);

	return 0;
}