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
 int get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_reg (struct vpe_dev*,int) ; 

__attribute__((used)) static int read_field_reg(struct vpe_dev *dev, int offset, u32 mask, int shift)
{
	return get_field(read_reg(dev, offset), mask, shift);
}