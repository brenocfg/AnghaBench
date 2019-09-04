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
struct nfp_app_bpf {int /*<<< orphan*/  tag_alloc_next; int /*<<< orphan*/  tag_allocator; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsg_warn (struct nfp_app_bpf*,char*) ; 
 scalar_t__ nfp_bpf_all_tags_busy (struct nfp_app_bpf*) ; 

__attribute__((used)) static int nfp_bpf_alloc_tag(struct nfp_app_bpf *bpf)
{
	/* All FW communication for BPF is request-reply.  To make sure we
	 * don't reuse the message ID too early after timeout - limit the
	 * number of requests in flight.
	 */
	if (nfp_bpf_all_tags_busy(bpf)) {
		cmsg_warn(bpf, "all FW request contexts busy!\n");
		return -EAGAIN;
	}

	WARN_ON(__test_and_set_bit(bpf->tag_alloc_next, bpf->tag_allocator));
	return bpf->tag_alloc_next++;
}