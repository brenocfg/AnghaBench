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
struct device {int dummy; } ;
typedef  enum dfl_id_type { ____Placeholder_dfl_id_type } dfl_id_type ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int DFL_ID_MAX ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_1__* dfl_devs ; 
 int /*<<< orphan*/  dfl_id_mutex ; 
 int idr_alloc (int /*<<< orphan*/ *,struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dfl_id_alloc(enum dfl_id_type type, struct device *dev)
{
	int id;

	WARN_ON(type >= DFL_ID_MAX);
	mutex_lock(&dfl_id_mutex);
	id = idr_alloc(&dfl_devs[type].id, dev, 0, 0, GFP_KERNEL);
	mutex_unlock(&dfl_id_mutex);

	return id;
}