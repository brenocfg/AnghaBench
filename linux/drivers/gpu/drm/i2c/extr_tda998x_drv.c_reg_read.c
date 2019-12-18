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
typedef  int /*<<< orphan*/  val ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct tda998x_priv {int dummy; } ;

/* Variables and functions */
 int reg_read_range (struct tda998x_priv*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int
reg_read(struct tda998x_priv *priv, u16 reg)
{
	u8 val = 0;
	int ret;

	ret = reg_read_range(priv, reg, &val, sizeof(val));
	if (ret < 0)
		return ret;
	return val;
}