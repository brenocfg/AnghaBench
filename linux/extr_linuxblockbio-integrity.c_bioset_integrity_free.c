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
struct bio_set {int /*<<< orphan*/  bvec_integrity_pool; int /*<<< orphan*/  bio_integrity_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 

void bioset_integrity_free(struct bio_set *bs)
{
	mempool_exit(&bs->bio_integrity_pool);
	mempool_exit(&bs->bvec_integrity_pool);
}