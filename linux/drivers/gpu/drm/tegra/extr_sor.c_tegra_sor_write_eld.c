#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t* eld; } ;
struct TYPE_4__ {TYPE_1__ connector; } ;
struct tegra_sor {TYPE_2__ output; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOR_AUDIO_HDA_ELD_BUFWR ; 
 size_t drm_eld_size (size_t*) ; 
 int /*<<< orphan*/  tegra_sor_writel (struct tegra_sor*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_sor_write_eld(struct tegra_sor *sor)
{
	size_t length = drm_eld_size(sor->output.connector.eld), i;

	for (i = 0; i < length; i++)
		tegra_sor_writel(sor, i << 8 | sor->output.connector.eld[i],
				 SOR_AUDIO_HDA_ELD_BUFWR);

	/*
	 * The HDA codec will always report an ELD buffer size of 96 bytes and
	 * the HDA codec driver will check that each byte read from the buffer
	 * is valid. Therefore every byte must be written, even if no 96 bytes
	 * were parsed from EDID.
	 */
	for (i = length; i < 96; i++)
		tegra_sor_writel(sor, i << 8 | 0, SOR_AUDIO_HDA_ELD_BUFWR);
}