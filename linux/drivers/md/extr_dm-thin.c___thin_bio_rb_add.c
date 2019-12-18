#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct rb_node* rb_node; } ;
struct thin_c {TYPE_4__ sort_bio_list; } ;
struct rb_node {struct rb_node* rb_right; struct rb_node* rb_left; } ;
struct dm_thin_endio_hook {int /*<<< orphan*/  rb_node; } ;
struct TYPE_5__ {scalar_t__ bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_6__ {scalar_t__ bi_sector; } ;
struct TYPE_7__ {TYPE_2__ bi_iter; } ;

/* Variables and functions */
 struct dm_thin_endio_hook* dm_per_bio_data (struct bio*,int) ; 
 int /*<<< orphan*/  rb_insert_color (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  rb_link_node (int /*<<< orphan*/ *,struct rb_node*,struct rb_node**) ; 
 TYPE_3__* thin_bio (struct dm_thin_endio_hook*) ; 
 struct dm_thin_endio_hook* thin_pbd (struct rb_node*) ; 

__attribute__((used)) static void __thin_bio_rb_add(struct thin_c *tc, struct bio *bio)
{
	struct rb_node **rbp, *parent;
	struct dm_thin_endio_hook *pbd;
	sector_t bi_sector = bio->bi_iter.bi_sector;

	rbp = &tc->sort_bio_list.rb_node;
	parent = NULL;
	while (*rbp) {
		parent = *rbp;
		pbd = thin_pbd(parent);

		if (bi_sector < thin_bio(pbd)->bi_iter.bi_sector)
			rbp = &(*rbp)->rb_left;
		else
			rbp = &(*rbp)->rb_right;
	}

	pbd = dm_per_bio_data(bio, sizeof(struct dm_thin_endio_hook));
	rb_link_node(&pbd->rb_node, parent, rbp);
	rb_insert_color(&pbd->rb_node, &tc->sort_bio_list);
}