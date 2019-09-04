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
 int /*<<< orphan*/  H_CSR ; 
 int /*<<< orphan*/  mei_me_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_me_hw (struct mei_device*) ; 
 int /*<<< orphan*/  trace_mei_reg_write (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mei_hcsr_write(struct mei_device *dev, u32 reg)
{
	trace_mei_reg_write(dev->dev, "H_CSR", H_CSR, reg);
	mei_me_reg_write(to_me_hw(dev), H_CSR, reg);
}