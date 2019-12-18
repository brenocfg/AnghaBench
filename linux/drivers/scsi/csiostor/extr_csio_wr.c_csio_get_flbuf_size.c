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
typedef  size_t uint32_t ;
struct csio_sge {int /*<<< orphan*/ * sge_fl_buf_size; } ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ SGE_FL_BUFFER_SIZE0_A ; 
 int /*<<< orphan*/  csio_rd_reg32 (struct csio_hw*,scalar_t__) ; 

__attribute__((used)) static void
csio_get_flbuf_size(struct csio_hw *hw, struct csio_sge *sge, uint32_t reg)
{
	sge->sge_fl_buf_size[reg] = csio_rd_reg32(hw, SGE_FL_BUFFER_SIZE0_A +
							reg * sizeof(uint32_t));
}