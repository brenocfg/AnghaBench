#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct era_metadata {TYPE_2__* writesets; TYPE_2__* current_writeset; int /*<<< orphan*/  block_size; struct block_device* bdev; } ;
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_3__ {void* root; } ;
struct TYPE_4__ {TYPE_1__ md; } ;

/* Variables and functions */
 struct era_metadata* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* INVALID_WRITESET_ROOT ; 
 int create_persistent_data_objects (struct era_metadata*,int) ; 
 int /*<<< orphan*/  kfree (struct era_metadata*) ; 
 struct era_metadata* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct era_metadata *metadata_open(struct block_device *bdev,
					  sector_t block_size,
					  bool may_format)
{
	int r;
	struct era_metadata *md = kzalloc(sizeof(*md), GFP_KERNEL);

	if (!md)
		return NULL;

	md->bdev = bdev;
	md->block_size = block_size;

	md->writesets[0].md.root = INVALID_WRITESET_ROOT;
	md->writesets[1].md.root = INVALID_WRITESET_ROOT;
	md->current_writeset = &md->writesets[0];

	r = create_persistent_data_objects(md, may_format);
	if (r) {
		kfree(md);
		return ERR_PTR(r);
	}

	return md;
}