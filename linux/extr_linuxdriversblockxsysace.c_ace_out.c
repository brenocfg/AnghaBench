#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct ace_device {TYPE_1__* reg_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* out ) (struct ace_device*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ace_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ace_out(struct ace_device *ace, int reg, u16 val)
{
	ace->reg_ops->out(ace, reg, val);
}