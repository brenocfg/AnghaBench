#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int sge_control; } ;
struct TYPE_4__ {TYPE_1__ sge; } ;
struct csio_hw {TYPE_2__ wrm; } ;

/* Variables and functions */
 int EGRSTATUSPAGESIZE_F ; 

__attribute__((used)) static inline uint32_t
csio_wr_qstat_pgsz(struct csio_hw *hw)
{
	return (hw->wrm.sge.sge_control & EGRSTATUSPAGESIZE_F) ?  128 : 64;
}