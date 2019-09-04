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
struct kyber_queue_data {TYPE_2__* domain_tokens; } ;
struct TYPE_3__ {unsigned int depth; } ;
struct TYPE_4__ {TYPE_1__ sb; } ;

/* Variables and functions */
#define  AWFUL 131 
#define  BAD 130 
#define  GOOD 129 
#define  GREAT 128 
 scalar_t__ IS_BAD (int) ; 
 scalar_t__ IS_GOOD (int) ; 
 int NONE ; 
 unsigned int clamp (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kyber_depth ; 
 unsigned int max (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sbitmap_queue_resize (TYPE_2__*,unsigned int) ; 

__attribute__((used)) static void kyber_adjust_rw_depth(struct kyber_queue_data *kqd,
				  unsigned int sched_domain, int this_status,
				  int other_status)
{
	unsigned int orig_depth, depth;

	/*
	 * If this domain had no samples, or reads and writes are both good or
	 * both bad, don't adjust the depth.
	 */
	if (this_status == NONE ||
	    (IS_GOOD(this_status) && IS_GOOD(other_status)) ||
	    (IS_BAD(this_status) && IS_BAD(other_status)))
		return;

	orig_depth = depth = kqd->domain_tokens[sched_domain].sb.depth;

	if (other_status == NONE) {
		depth++;
	} else {
		switch (this_status) {
		case GOOD:
			if (other_status == AWFUL)
				depth -= max(depth / 4, 1U);
			else
				depth -= max(depth / 8, 1U);
			break;
		case GREAT:
			if (other_status == AWFUL)
				depth /= 2;
			else
				depth -= max(depth / 4, 1U);
			break;
		case BAD:
			depth++;
			break;
		case AWFUL:
			if (other_status == GREAT)
				depth += 2;
			else
				depth++;
			break;
		}
	}

	depth = clamp(depth, 1U, kyber_depth[sched_domain]);
	if (depth != orig_depth)
		sbitmap_queue_resize(&kqd->domain_tokens[sched_domain], depth);
}