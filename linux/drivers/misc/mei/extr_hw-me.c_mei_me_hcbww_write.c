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
struct mei_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_CB_WW ; 
 int /*<<< orphan*/  mei_me_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_me_hw (struct mei_device*) ; 

__attribute__((used)) static inline void mei_me_hcbww_write(struct mei_device *dev, u32 data)
{
	mei_me_reg_write(to_me_hw(dev), H_CB_WW, data);
}