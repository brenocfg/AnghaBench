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
struct writeset_disk {int dummy; } ;
struct dm_btree_value_type {int size; int /*<<< orphan*/  equal; int /*<<< orphan*/  dec; int /*<<< orphan*/  inc; struct era_metadata* context; } ;
struct TYPE_2__ {int levels; int /*<<< orphan*/  tm; struct dm_btree_value_type value_type; } ;
struct era_metadata {TYPE_1__ writeset_tree_info; int /*<<< orphan*/  tm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ws_dec ; 
 int /*<<< orphan*/  ws_eq ; 
 int /*<<< orphan*/  ws_inc ; 

__attribute__((used)) static void setup_writeset_tree_info(struct era_metadata *md)
{
	struct dm_btree_value_type *vt = &md->writeset_tree_info.value_type;
	md->writeset_tree_info.tm = md->tm;
	md->writeset_tree_info.levels = 1;
	vt->context = md;
	vt->size = sizeof(struct writeset_disk);
	vt->inc = ws_inc;
	vt->dec = ws_dec;
	vt->equal = ws_eq;
}