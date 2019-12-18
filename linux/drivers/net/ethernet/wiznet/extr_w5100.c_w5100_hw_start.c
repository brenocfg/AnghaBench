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
typedef  int /*<<< orphan*/  u8 ;
struct w5100_priv {TYPE_1__* ops; int /*<<< orphan*/  promisc; } ;
struct TYPE_2__ {scalar_t__ chip_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  S0_CR_OPEN ; 
 int /*<<< orphan*/  S0_MR_MACRAW ; 
 int /*<<< orphan*/  S0_MR_MF ; 
 int /*<<< orphan*/  W5100_S0_MR (struct w5100_priv*) ; 
 scalar_t__ W5500 ; 
 int /*<<< orphan*/  W5500_S0_MR_MF ; 
 int /*<<< orphan*/  w5100_command (struct w5100_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w5100_enable_intr (struct w5100_priv*) ; 
 int /*<<< orphan*/  w5100_write (struct w5100_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void w5100_hw_start(struct w5100_priv *priv)
{
	u8 mode = S0_MR_MACRAW;

	if (!priv->promisc) {
		if (priv->ops->chip_id == W5500)
			mode |= W5500_S0_MR_MF;
		else
			mode |= S0_MR_MF;
	}

	w5100_write(priv, W5100_S0_MR(priv), mode);
	w5100_command(priv, S0_CR_OPEN);
	w5100_enable_intr(priv);
}