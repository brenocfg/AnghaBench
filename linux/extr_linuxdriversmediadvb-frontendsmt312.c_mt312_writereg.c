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
struct mt312_state {int dummy; } ;
typedef  enum mt312_reg_addr { ____Placeholder_mt312_reg_addr } mt312_reg_addr ;

/* Variables and functions */
 int mt312_write (struct mt312_state*,int const,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int mt312_writereg(struct mt312_state *state,
				 const enum mt312_reg_addr reg, const u8 val)
{
	u8 tmp = val; /* see gcc.gnu.org/bugzilla/show_bug.cgi?id=81715 */


	return mt312_write(state, reg, &tmp, 1);
}