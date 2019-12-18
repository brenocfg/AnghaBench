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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {TYPE_1__* regs; scalar_t__ little_endian; } ;
struct TYPE_3__ {int /*<<< orphan*/  svr; } ;

/* Variables and functions */
 TYPE_2__* guts ; 
 int /*<<< orphan*/  ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioread32be (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 fsl_guts_get_svr(void)
{
	u32 svr = 0;

	if (!guts || !guts->regs)
		return svr;

	if (guts->little_endian)
		svr = ioread32(&guts->regs->svr);
	else
		svr = ioread32be(&guts->regs->svr);

	return svr;
}