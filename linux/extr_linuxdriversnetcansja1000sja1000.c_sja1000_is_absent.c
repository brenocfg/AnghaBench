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
struct sja1000_priv {int (* read_reg ) (struct sja1000_priv*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SJA1000_MOD ; 
 int stub1 (struct sja1000_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sja1000_is_absent(struct sja1000_priv *priv)
{
	return (priv->read_reg(priv, SJA1000_MOD) == 0xFF);
}