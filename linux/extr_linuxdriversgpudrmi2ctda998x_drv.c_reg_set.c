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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct tda998x_priv {int dummy; } ;

/* Variables and functions */
 int reg_read (struct tda998x_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct tda998x_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
reg_set(struct tda998x_priv *priv, u16 reg, u8 val)
{
	int old_val;

	old_val = reg_read(priv, reg);
	if (old_val >= 0)
		reg_write(priv, reg, old_val | val);
}