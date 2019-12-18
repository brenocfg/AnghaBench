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
struct iscsi_segment {size_t size; void* data; } ;
struct ahash_request {int dummy; } ;
typedef  int /*<<< orphan*/  iscsi_segment_done_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  __iscsi_segment_init (struct iscsi_segment*,size_t,int /*<<< orphan*/ *,struct ahash_request*) ; 

inline void
iscsi_segment_init_linear(struct iscsi_segment *segment, void *data,
			  size_t size, iscsi_segment_done_fn_t *done,
			  struct ahash_request *hash)
{
	__iscsi_segment_init(segment, size, done, hash);
	segment->data = data;
	segment->size = size;
}