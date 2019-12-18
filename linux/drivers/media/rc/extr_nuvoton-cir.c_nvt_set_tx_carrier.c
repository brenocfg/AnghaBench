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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct rc_dev {struct nvt_dev* priv; } ;
struct nvt_dev {int dummy; } ;
typedef  int carrier ;

/* Variables and functions */
 int /*<<< orphan*/  CIR_CC ; 
 int /*<<< orphan*/  CIR_CP ; 
 int EINVAL ; 
 int /*<<< orphan*/  nvt_cir_reg_read (struct nvt_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvt_cir_reg_write (struct nvt_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvt_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvt_set_tx_carrier(struct rc_dev *dev, u32 carrier)
{
	struct nvt_dev *nvt = dev->priv;
	u16 val;

	if (carrier == 0)
		return -EINVAL;

	nvt_cir_reg_write(nvt, 1, CIR_CP);
	val = 3000000 / (carrier) - 1;
	nvt_cir_reg_write(nvt, val & 0xff, CIR_CC);

	nvt_dbg("cp: 0x%x cc: 0x%x\n",
		nvt_cir_reg_read(nvt, CIR_CP), nvt_cir_reg_read(nvt, CIR_CC));

	return 0;
}