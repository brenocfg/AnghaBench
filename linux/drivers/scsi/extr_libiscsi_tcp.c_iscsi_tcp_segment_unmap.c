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
struct iscsi_segment {int /*<<< orphan*/ * data; int /*<<< orphan*/ * sg_mapped; int /*<<< orphan*/  sg; scalar_t__ atomic_mapped; } ;

/* Variables and functions */
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_page (int /*<<< orphan*/ ) ; 

void iscsi_tcp_segment_unmap(struct iscsi_segment *segment)
{
	if (segment->sg_mapped) {
		if (segment->atomic_mapped)
			kunmap_atomic(segment->sg_mapped);
		else
			kunmap(sg_page(segment->sg));
		segment->sg_mapped = NULL;
		segment->data = NULL;
	}
}