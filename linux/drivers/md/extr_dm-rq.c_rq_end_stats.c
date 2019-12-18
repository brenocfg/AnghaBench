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
struct request {int dummy; } ;
struct mapped_device {int /*<<< orphan*/  stats; } ;
struct dm_rq_target_io {int /*<<< orphan*/  stats_aux; scalar_t__ duration_jiffies; int /*<<< orphan*/  n_sectors; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 
 int /*<<< orphan*/  dm_stats_account_io (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_stats_used (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  rq_data_dir (struct request*) ; 
 struct dm_rq_target_io* tio_from_request (struct request*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rq_end_stats(struct mapped_device *md, struct request *orig)
{
	if (unlikely(dm_stats_used(&md->stats))) {
		struct dm_rq_target_io *tio = tio_from_request(orig);
		tio->duration_jiffies = jiffies - tio->duration_jiffies;
		dm_stats_account_io(&md->stats, rq_data_dir(orig),
				    blk_rq_pos(orig), tio->n_sectors, true,
				    tio->duration_jiffies, &tio->stats_aux);
	}
}