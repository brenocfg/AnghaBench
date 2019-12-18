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
struct nfp_ccm {int /*<<< orphan*/  tag_alloc_next; int /*<<< orphan*/  tag_allocator; int /*<<< orphan*/  app; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccm_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nfp_ccm_all_tags_busy (struct nfp_ccm*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfp_ccm_alloc_tag(struct nfp_ccm *ccm)
{
	/* CCM is for FW communication which is request-reply.  To make sure
	 * we don't reuse the message ID too early after timeout - limit the
	 * number of requests in flight.
	 */
	if (unlikely(nfp_ccm_all_tags_busy(ccm))) {
		ccm_warn(ccm->app, "all FW request contexts busy!\n");
		return -EAGAIN;
	}

	WARN_ON(__test_and_set_bit(ccm->tag_alloc_next, ccm->tag_allocator));
	return ccm->tag_alloc_next++;
}