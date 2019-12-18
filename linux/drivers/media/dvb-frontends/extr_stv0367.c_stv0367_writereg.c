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
typedef  int /*<<< orphan*/  u16 ;
struct stv0367_state {int dummy; } ;

/* Variables and functions */
 int stv0367_writeregs (struct stv0367_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int stv0367_writereg(struct stv0367_state *state, u16 reg, u8 data)
{
	u8 tmp = data; /* see gcc.gnu.org/bugzilla/show_bug.cgi?id=81715 */

	return stv0367_writeregs(state, reg, &tmp, 1);
}