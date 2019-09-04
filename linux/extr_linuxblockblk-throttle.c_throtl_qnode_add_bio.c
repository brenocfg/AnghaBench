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
struct throtl_qnode {int /*<<< orphan*/  tg; int /*<<< orphan*/  node; int /*<<< orphan*/  bios; } ;
struct list_head {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  blkg_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tg_to_blkg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void throtl_qnode_add_bio(struct bio *bio, struct throtl_qnode *qn,
				 struct list_head *queued)
{
	bio_list_add(&qn->bios, bio);
	if (list_empty(&qn->node)) {
		list_add_tail(&qn->node, queued);
		blkg_get(tg_to_blkg(qn->tg));
	}
}