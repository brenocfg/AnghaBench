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
 int /*<<< orphan*/  lgs8gxx_read_reg (struct lgs8gxx_state*,int,int*) ; 
 int /*<<< orphan*/  lgs8gxx_write_reg (struct lgs8gxx_state*,int,int) ; 

__attribute__((used)) static void packet_counter_start(struct lgs8gxx_state *priv)
{
	u8 orig, t;

	if (priv->config->prod == LGS8GXX_PROD_LGS8G75) {
		lgs8gxx_read_reg(priv, 0x30, &orig);
		orig &= 0xE7;
		t = orig | 0x10;
		lgs8gxx_write_reg(priv, 0x30, t);
		t = orig | 0x18;
		lgs8gxx_write_reg(priv, 0x30, t);
		t = orig | 0x10;
		lgs8gxx_write_reg(priv, 0x30, t);
	} else {
		lgs8gxx_write_reg(priv, 0xC6, 0x01);
		lgs8gxx_write_reg(priv, 0xC6, 0x41);
		lgs8gxx_write_reg(priv, 0xC6, 0x01);
	}
}