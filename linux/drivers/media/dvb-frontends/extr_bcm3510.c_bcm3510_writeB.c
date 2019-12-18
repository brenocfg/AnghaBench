#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct bcm3510_state {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  raw; } ;
typedef  TYPE_1__ bcm3510_register_value ;

/* Variables and functions */
 int bcm3510_writebytes (struct bcm3510_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int bcm3510_writeB(struct bcm3510_state *state, u8 reg, bcm3510_register_value v)
{
	return bcm3510_writebytes(state,reg,&v.raw,1);
}