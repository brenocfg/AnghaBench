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
struct tda998x_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_CEC_ENAMODS ; 
 int cec_read (struct tda998x_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_write (struct tda998x_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cec_enamods(struct tda998x_priv *priv, u8 mods, bool enable)
{
	int val = cec_read(priv, REG_CEC_ENAMODS);

	if (val < 0)
		return;

	if (enable)
		val |= mods;
	else
		val &= ~mods;

	cec_write(priv, REG_CEC_ENAMODS, val);
}