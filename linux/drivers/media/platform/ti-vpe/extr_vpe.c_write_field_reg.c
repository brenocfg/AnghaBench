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
typedef  int /*<<< orphan*/  u32 ;
struct vpe_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_reg (struct vpe_dev*,int) ; 
 int /*<<< orphan*/  write_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_reg (struct vpe_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_field_reg(struct vpe_dev *dev, int offset, u32 field,
		u32 mask, int shift)
{
	u32 val = read_reg(dev, offset);

	write_field(&val, field, mask, shift);

	write_reg(dev, offset, val);
}