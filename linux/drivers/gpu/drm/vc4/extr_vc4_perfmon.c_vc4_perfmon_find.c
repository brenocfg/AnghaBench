#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vc4_perfmon {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  idr; } ;
struct vc4_file {TYPE_1__ perfmon; } ;

/* Variables and functions */
 struct vc4_perfmon* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc4_perfmon_get (struct vc4_perfmon*) ; 

struct vc4_perfmon *vc4_perfmon_find(struct vc4_file *vc4file, int id)
{
	struct vc4_perfmon *perfmon;

	mutex_lock(&vc4file->perfmon.lock);
	perfmon = idr_find(&vc4file->perfmon.idr, id);
	vc4_perfmon_get(perfmon);
	mutex_unlock(&vc4file->perfmon.lock);

	return perfmon;
}