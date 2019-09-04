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
typedef  int /*<<< orphan*/  u16 ;
struct nfp_app_bpf {scalar_t__ tag_alloc_last; scalar_t__ tag_alloc_next; int /*<<< orphan*/  tag_allocator; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_bpf_free_tag(struct nfp_app_bpf *bpf, u16 tag)
{
	WARN_ON(!__test_and_clear_bit(tag, bpf->tag_allocator));

	while (!test_bit(bpf->tag_alloc_last, bpf->tag_allocator) &&
	       bpf->tag_alloc_last != bpf->tag_alloc_next)
		bpf->tag_alloc_last++;
}