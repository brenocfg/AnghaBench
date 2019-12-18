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
struct gbe_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gbe_reset_mod_stats (struct gbe_priv*,int) ; 
 int /*<<< orphan*/  gbe_stats_mod_visible_ver14 (struct gbe_priv*,int) ; 

__attribute__((used)) static void gbe_reset_mod_stats_ver14(struct gbe_priv *gbe_dev, int stats_mod)
{
	gbe_stats_mod_visible_ver14(gbe_dev, stats_mod);
	gbe_reset_mod_stats(gbe_dev, stats_mod);
}