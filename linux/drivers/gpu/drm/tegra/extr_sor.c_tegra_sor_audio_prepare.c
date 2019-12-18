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
typedef  int u32 ;
struct tegra_sor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOR_AUDIO_HDA_PRESENSE ; 
 int SOR_AUDIO_HDA_PRESENSE_ELDV ; 
 int SOR_AUDIO_HDA_PRESENSE_PD ; 
 int /*<<< orphan*/  tegra_sor_write_eld (struct tegra_sor*) ; 
 int /*<<< orphan*/  tegra_sor_writel (struct tegra_sor*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_sor_audio_prepare(struct tegra_sor *sor)
{
	u32 value;

	tegra_sor_write_eld(sor);

	value = SOR_AUDIO_HDA_PRESENSE_ELDV | SOR_AUDIO_HDA_PRESENSE_PD;
	tegra_sor_writel(sor, value, SOR_AUDIO_HDA_PRESENSE);
}