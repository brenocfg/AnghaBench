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
struct switchtec_ntb {int nr_direct_mw; } ;
struct ntb_dev {int dummy; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 struct switchtec_ntb* ntb_sndev (struct ntb_dev*) ; 
 int switchtec_ntb_direct_get_addr (struct switchtec_ntb*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int switchtec_ntb_lut_get_addr (struct switchtec_ntb*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int switchtec_ntb_peer_mw_count (struct ntb_dev*) ; 

__attribute__((used)) static int switchtec_ntb_peer_mw_get_addr(struct ntb_dev *ntb, int idx,
					  phys_addr_t *base,
					  resource_size_t *size)
{
	struct switchtec_ntb *sndev = ntb_sndev(ntb);

	if (idx < sndev->nr_direct_mw)
		return switchtec_ntb_direct_get_addr(sndev, idx, base, size);
	else if (idx < switchtec_ntb_peer_mw_count(ntb))
		return switchtec_ntb_lut_get_addr(sndev, idx, base, size);
	else
		return -EINVAL;
}