#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct switchtec_ntb {int peer_nr_direct_mw; TYPE_1__* peer_shared; } ;
struct ntb_dev {int dummy; } ;
typedef  scalar_t__ resource_size_t ;
struct TYPE_2__ {int /*<<< orphan*/ * mw_sizes; } ;

/* Variables and functions */
 int EINVAL ; 
 int NTB_DEF_PEER_IDX ; 
 scalar_t__ SZ_4K ; 
 scalar_t__ ioread64 (int /*<<< orphan*/ *) ; 
 struct switchtec_ntb* ntb_sndev (struct ntb_dev*) ; 

__attribute__((used)) static int switchtec_ntb_mw_get_align(struct ntb_dev *ntb, int pidx,
				      int widx, resource_size_t *addr_align,
				      resource_size_t *size_align,
				      resource_size_t *size_max)
{
	struct switchtec_ntb *sndev = ntb_sndev(ntb);
	int lut;
	resource_size_t size;

	if (pidx != NTB_DEF_PEER_IDX)
		return -EINVAL;

	lut = widx >= sndev->peer_nr_direct_mw;
	size = ioread64(&sndev->peer_shared->mw_sizes[widx]);

	if (size == 0)
		return -EINVAL;

	if (addr_align)
		*addr_align = lut ? size : SZ_4K;

	if (size_align)
		*size_align = lut ? size : SZ_4K;

	if (size_max)
		*size_max = size;

	return 0;
}