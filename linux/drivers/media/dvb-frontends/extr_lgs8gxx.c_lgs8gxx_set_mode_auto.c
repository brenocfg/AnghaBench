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
typedef  scalar_t__ u8 ;
struct lgs8gxx_state {TYPE_1__* config; } ;
struct TYPE_2__ {scalar_t__ prod; } ;

/* Variables and functions */
 scalar_t__ LGS8GXX_PROD_LGS8913 ; 
 scalar_t__ LGS8GXX_PROD_LGS8G42 ; 
 scalar_t__ LGS8GXX_PROD_LGS8G52 ; 
 scalar_t__ LGS8GXX_PROD_LGS8G54 ; 
 scalar_t__ LGS8GXX_PROD_LGS8G75 ; 
 scalar_t__ LGS8GXX_PROD_LGS8GL5 ; 
 int /*<<< orphan*/  lgs8gxx_read_reg (struct lgs8gxx_state*,int,scalar_t__*) ; 
 int /*<<< orphan*/  lgs8gxx_write_reg (struct lgs8gxx_state*,int,int) ; 

__attribute__((used)) static int lgs8gxx_set_mode_auto(struct lgs8gxx_state *priv)
{
	u8 t;
	u8 prod = priv->config->prod;

	if (prod == LGS8GXX_PROD_LGS8913)
		lgs8gxx_write_reg(priv, 0xC6, 0x01);

	if (prod == LGS8GXX_PROD_LGS8G75) {
		lgs8gxx_read_reg(priv, 0x0C, &t);
		t &= (~0x04);
		lgs8gxx_write_reg(priv, 0x0C, t | 0x80);
		lgs8gxx_write_reg(priv, 0x39, 0x00);
		lgs8gxx_write_reg(priv, 0x3D, 0x04);
	} else if (prod == LGS8GXX_PROD_LGS8913 ||
		prod == LGS8GXX_PROD_LGS8GL5 ||
		prod == LGS8GXX_PROD_LGS8G42 ||
		prod == LGS8GXX_PROD_LGS8G52 ||
		prod == LGS8GXX_PROD_LGS8G54) {
		lgs8gxx_read_reg(priv, 0x7E, &t);
		lgs8gxx_write_reg(priv, 0x7E, t | 0x01);

		/* clear FEC self reset */
		lgs8gxx_read_reg(priv, 0xC5, &t);
		lgs8gxx_write_reg(priv, 0xC5, t & 0xE0);
	}

	if (prod == LGS8GXX_PROD_LGS8913) {
		/* FEC auto detect */
		lgs8gxx_write_reg(priv, 0xC1, 0x03);

		lgs8gxx_read_reg(priv, 0x7C, &t);
		t = (t & 0x8C) | 0x03;
		lgs8gxx_write_reg(priv, 0x7C, t);

		/* BER test mode */
		lgs8gxx_read_reg(priv, 0xC3, &t);
		t = (t & 0xEF) |  0x10;
		lgs8gxx_write_reg(priv, 0xC3, t);
	}

	if (priv->config->prod == LGS8GXX_PROD_LGS8G52)
		lgs8gxx_write_reg(priv, 0xD9, 0x40);

	return 0;
}