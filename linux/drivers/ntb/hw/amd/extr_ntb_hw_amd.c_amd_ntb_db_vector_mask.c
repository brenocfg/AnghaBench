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
typedef  unsigned long long u64 ;
struct ntb_dev {int dummy; } ;
struct amd_ntb_dev {int db_count; unsigned long long db_valid_mask; } ;

/* Variables and functions */
 struct amd_ntb_dev* ntb_ndev (struct ntb_dev*) ; 

__attribute__((used)) static u64 amd_ntb_db_vector_mask(struct ntb_dev *ntb, int db_vector)
{
	struct amd_ntb_dev *ndev = ntb_ndev(ntb);

	if (db_vector < 0 || db_vector > ndev->db_count)
		return 0;

	return ntb_ndev(ntb)->db_valid_mask & (1ULL << db_vector);
}