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
typedef  int u64 ;
struct switchtec_ntb {int db_mask; int db_shift; int db_valid_mask; } ;
struct ntb_dev {int dummy; } ;

/* Variables and functions */
 struct switchtec_ntb* ntb_sndev (struct ntb_dev*) ; 

__attribute__((used)) static u64 switchtec_ntb_db_read_mask(struct ntb_dev *ntb)
{
	struct switchtec_ntb *sndev = ntb_sndev(ntb);

	return (sndev->db_mask >> sndev->db_shift) & sndev->db_valid_mask;
}