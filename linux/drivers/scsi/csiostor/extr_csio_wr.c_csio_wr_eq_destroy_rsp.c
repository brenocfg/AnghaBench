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
struct csio_mb {int dummy; } ;
struct csio_hw {int /*<<< orphan*/  mb_mempool; } ;
typedef  enum fw_retval { ____Placeholder_fw_retval } fw_retval ;

/* Variables and functions */
 int EINVAL ; 
 int FW_SUCCESS ; 
 int csio_mb_fw_retval (struct csio_mb*) ; 
 int /*<<< orphan*/  mempool_free (struct csio_mb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
csio_wr_eq_destroy_rsp(struct csio_hw *hw, struct csio_mb *mbp, int eq_idx)
{
	enum fw_retval retval = csio_mb_fw_retval(mbp);
	int rv = 0;

	if (retval != FW_SUCCESS)
		rv = -EINVAL;

	mempool_free(mbp, hw->mb_mempool);

	return rv;
}