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
typedef  int u8 ;
struct lgs8gxx_state {TYPE_1__* config; } ;
struct TYPE_2__ {scalar_t__ prod; } ;

/* Variables and functions */
 scalar_t__ LGS8GXX_PROD_LGS8G75 ; 
 int lgs8gxx_read_reg (struct lgs8gxx_state*,int,int*) ; 

__attribute__((used)) static int lgs8gxx_is_locked(struct lgs8gxx_state *priv, u8 *locked)
{
	int ret = 0;
	u8 t;

	if (priv->config->prod == LGS8GXX_PROD_LGS8G75)
		ret = lgs8gxx_read_reg(priv, 0x13, &t);
	else
		ret = lgs8gxx_read_reg(priv, 0x4B, &t);
	if (ret != 0)
		return ret;

	if (priv->config->prod == LGS8GXX_PROD_LGS8G75)
		*locked = ((t & 0x80) == 0x80) ? 1 : 0;
	else
		*locked = ((t & 0xC0) == 0xC0) ? 1 : 0;
	return 0;
}