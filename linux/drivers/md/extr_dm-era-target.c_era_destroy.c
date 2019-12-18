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
struct era {scalar_t__ metadata_dev; int /*<<< orphan*/  ti; scalar_t__ origin_dev; scalar_t__ wq; scalar_t__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  dm_put_device (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct era*) ; 
 int /*<<< orphan*/  metadata_close (scalar_t__) ; 

__attribute__((used)) static void era_destroy(struct era *era)
{
	if (era->md)
		metadata_close(era->md);

	if (era->wq)
		destroy_workqueue(era->wq);

	if (era->origin_dev)
		dm_put_device(era->ti, era->origin_dev);

	if (era->metadata_dev)
		dm_put_device(era->ti, era->metadata_dev);

	kfree(era);
}