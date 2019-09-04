#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {unsigned long page; int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {unsigned long offset; void* page; } ;
struct TYPE_13__ {TYPE_5__ virt; TYPE_1__ phys; } ;
struct TYPE_10__ {unsigned long page; int /*<<< orphan*/  addr; } ;
struct TYPE_9__ {unsigned long offset; void* page; } ;
struct TYPE_11__ {TYPE_3__ virt; TYPE_2__ phys; } ;
struct TYPE_14__ {int /*<<< orphan*/  offset; } ;
struct skcipher_walk {int flags; TYPE_6__ src; TYPE_4__ dst; TYPE_7__ out; TYPE_7__ in; } ;

/* Variables and functions */
 int SKCIPHER_WALK_DIFF ; 
 int SKCIPHER_WALK_PHYS ; 
 void* offset_in_page (int /*<<< orphan*/ ) ; 
 void* scatterwalk_page (TYPE_7__*) ; 
 int /*<<< orphan*/  skcipher_map_dst (struct skcipher_walk*) ; 
 int /*<<< orphan*/  skcipher_map_src (struct skcipher_walk*) ; 

__attribute__((used)) static int skcipher_next_fast(struct skcipher_walk *walk)
{
	unsigned long diff;

	walk->src.phys.page = scatterwalk_page(&walk->in);
	walk->src.phys.offset = offset_in_page(walk->in.offset);
	walk->dst.phys.page = scatterwalk_page(&walk->out);
	walk->dst.phys.offset = offset_in_page(walk->out.offset);

	if (walk->flags & SKCIPHER_WALK_PHYS)
		return 0;

	diff = walk->src.phys.offset - walk->dst.phys.offset;
	diff |= walk->src.virt.page - walk->dst.virt.page;

	skcipher_map_src(walk);
	walk->dst.virt.addr = walk->src.virt.addr;

	if (diff) {
		walk->flags |= SKCIPHER_WALK_DIFF;
		skcipher_map_dst(walk);
	}

	return 0;
}