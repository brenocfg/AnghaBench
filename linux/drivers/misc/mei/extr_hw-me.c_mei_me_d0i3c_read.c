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
struct mei_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_D0I3C ; 
 int /*<<< orphan*/  mei_me_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_me_hw (struct mei_device const*) ; 
 int /*<<< orphan*/  trace_mei_reg_read (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 mei_me_d0i3c_read(const struct mei_device *dev)
{
	u32 reg;

	reg = mei_me_reg_read(to_me_hw(dev), H_D0I3C);
	trace_mei_reg_read(dev->dev, "H_D0I3C", H_D0I3C, reg);

	return reg;
}