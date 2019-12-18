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
struct genwqe_dev {int softreset; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IO_SLU_BITSTREAM ; 
 int __genwqe_readq (struct genwqe_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genwqe_is_privileged (struct genwqe_dev*) ; 

int genwqe_read_softreset(struct genwqe_dev *cd)
{
	u64 bitstream;

	if (!genwqe_is_privileged(cd))
		return -ENODEV;

	bitstream = __genwqe_readq(cd, IO_SLU_BITSTREAM) & 0x1;
	cd->softreset = (bitstream == 0) ? 0x8ull : 0xcull;
	return 0;
}