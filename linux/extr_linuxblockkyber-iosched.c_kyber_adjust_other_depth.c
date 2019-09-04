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
 size_t KYBER_OTHER ; 
 int NONE ; 
 unsigned int clamp (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kyber_depth ; 
 unsigned int max (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sbitmap_queue_resize (TYPE_2__*,unsigned int) ; 

__attribute__((used)) static void kyber_adjust_other_depth(struct kyber_queue_data *kqd,
				     int read_status, int write_status,
				     bool have_samples)
{
	unsigned int orig_depth, depth;
	int status;

	orig_depth = depth = kqd->domain_tokens[KYBER_OTHER].sb.depth;

	if (read_status == NONE && write_status == NONE) {
		depth += 2;
	} else if (have_samples) {
		if (read_status == NONE)
			status = write_status;
		else if (write_status == NONE)
			status = read_status;
		else
			status = max(read_status, write_status);
		switch (status) {
		case GREAT:
			depth += 2;
			break;
		case GOOD:
			depth++;
			break;
		case BAD:
			depth -= max(depth / 4, 1U);
			break;
		case AWFUL:
			depth /= 2;
			break;
		}
	}

	depth = clamp(depth, 1U, kyber_depth[KYBER_OTHER]);
	if (depth != orig_depth)
		sbitmap_queue_resize(&kqd->domain_tokens[KYBER_OTHER], depth);
}