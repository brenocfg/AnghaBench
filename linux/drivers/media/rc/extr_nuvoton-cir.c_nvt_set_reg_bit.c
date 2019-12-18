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
typedef  int u8 ;
struct nvt_dev {int dummy; } ;

/* Variables and functions */
 int nvt_cr_read (struct nvt_dev*,int) ; 
 int /*<<< orphan*/  nvt_cr_write (struct nvt_dev*,int,int) ; 

__attribute__((used)) static inline void nvt_set_reg_bit(struct nvt_dev *nvt, u8 val, u8 reg)
{
	u8 tmp = nvt_cr_read(nvt, reg) | val;
	nvt_cr_write(nvt, tmp, reg);
}