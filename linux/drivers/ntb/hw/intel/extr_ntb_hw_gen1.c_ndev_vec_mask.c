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
struct intel_ntb_dev {int db_vec_shift; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 

__attribute__((used)) static inline u64 ndev_vec_mask(struct intel_ntb_dev *ndev, int db_vector)
{
	u64 shift, mask;

	shift = ndev->db_vec_shift;
	mask = BIT_ULL(shift) - 1;

	return mask << (shift * db_vector);
}