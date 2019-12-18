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
struct dm_target {struct clone* private; } ;
struct clone {int /*<<< orphan*/  ios_in_flight; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int DM_ENDIO_DONE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int clone_endio(struct dm_target *ti, struct bio *bio, blk_status_t *error)
{
	struct clone *clone = ti->private;

	atomic_dec(&clone->ios_in_flight);

	return DM_ENDIO_DONE;
}