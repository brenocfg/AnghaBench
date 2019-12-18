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
struct switchtec_ntb {int nr_lut_mw; int nr_rsvd_luts; int nr_direct_mw; } ;
struct ntb_dev {int dummy; } ;

/* Variables and functions */
 struct switchtec_ntb* ntb_sndev (struct ntb_dev*) ; 
 scalar_t__ use_lut_mws ; 

__attribute__((used)) static int switchtec_ntb_peer_mw_count(struct ntb_dev *ntb)
{
	struct switchtec_ntb *sndev = ntb_sndev(ntb);
	int nr_lut_mw = sndev->nr_lut_mw - sndev->nr_rsvd_luts;

	return sndev->nr_direct_mw + (use_lut_mws ? nr_lut_mw : 0);
}