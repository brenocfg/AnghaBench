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
typedef  size_t u8 ;
struct stb6100_state {int dummy; } ;
struct TYPE_2__ {size_t mask; size_t set; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  FE_ERROR ; 
 size_t STB6100_NUMREGS ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,size_t) ; 
 TYPE_1__* stb6100_template ; 
 int stb6100_write_reg_range (struct stb6100_state*,size_t*,size_t,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int stb6100_write_reg(struct stb6100_state *state, u8 reg, u8 data)
{
	u8 tmp = data; /* see gcc.gnu.org/bugzilla/show_bug.cgi?id=81715 */

	if (unlikely(reg >= STB6100_NUMREGS)) {
		dprintk(verbose, FE_ERROR, 1, "Invalid register offset 0x%x", reg);
		return -EREMOTEIO;
	}
	tmp = (tmp & stb6100_template[reg].mask) | stb6100_template[reg].set;
	return stb6100_write_reg_range(state, &tmp, reg, 1);
}