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
struct il_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_UCODE_DRV_GP2 ; 
 int _il_rd (struct il_priv*,int /*<<< orphan*/ ) ; 

int
il3945_hw_get_temperature(struct il_priv *il)
{
	return _il_rd(il, CSR_UCODE_DRV_GP2);
}