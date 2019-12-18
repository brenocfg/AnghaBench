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
struct sja1105_reset_cmd {int cold_rst; int /*<<< orphan*/  member_0; } ;
struct sja1105_private {TYPE_1__* info; } ;
struct TYPE_2__ {int (* reset_cmd ) (struct sja1105_private const*,struct sja1105_reset_cmd*) ;} ;

/* Variables and functions */
 int stub1 (struct sja1105_private const*,struct sja1105_reset_cmd*) ; 

__attribute__((used)) static int sja1105_cold_reset(const struct sja1105_private *priv)
{
	struct sja1105_reset_cmd reset = {0};

	reset.cold_rst = 1;
	return priv->info->reset_cmd(priv, &reset);
}