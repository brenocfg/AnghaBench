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
struct qxl_release {int /*<<< orphan*/  bos; int /*<<< orphan*/  ticket; } ;

/* Variables and functions */
 scalar_t__ list_is_singular (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_eu_backoff_reservation (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void qxl_release_backoff_reserve_list(struct qxl_release *release)
{
	/* if only one object on the release its the release itself
	   since these objects are pinned no need to reserve */
	if (list_is_singular(&release->bos))
		return;

	ttm_eu_backoff_reservation(&release->ticket, &release->bos);
}