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
struct ocelot_acl_block {struct ocelot* ocelot; scalar_t__ count; int /*<<< orphan*/  rules; } ;
struct ocelot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct ocelot_acl_block* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ocelot_acl_block *ocelot_acl_block_create(struct ocelot *ocelot)
{
	struct ocelot_acl_block *block;

	block = kzalloc(sizeof(*block), GFP_KERNEL);
	if (!block)
		return NULL;

	INIT_LIST_HEAD(&block->rules);
	block->count = 0;
	block->ocelot = ocelot;

	return block;
}