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
typedef  int /*<<< orphan*/  u8 ;
struct stv6110x_state {int dummy; } ;

/* Variables and functions */
 int stv6110x_write_regs (struct stv6110x_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int stv6110x_write_reg(struct stv6110x_state *stv6110x, u8 reg, u8 data)
{
	u8 tmp = data; /* see gcc.gnu.org/bugzilla/show_bug.cgi?id=81715 */

	return stv6110x_write_regs(stv6110x, reg, &tmp, 1);
}