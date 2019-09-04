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
struct r10conf {int /*<<< orphan*/  r10buf_pool; } ;
struct r10bio {TYPE_1__* mddev; } ;
struct TYPE_2__ {struct r10conf* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  lower_barrier (struct r10conf*) ; 
 int /*<<< orphan*/  mempool_free (struct r10bio*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_buf(struct r10bio *r10_bio)
{
	struct r10conf *conf = r10_bio->mddev->private;

	mempool_free(r10_bio, &conf->r10buf_pool);

	lower_barrier(conf);
}