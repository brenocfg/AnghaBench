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
typedef  int /*<<< orphan*/  u32 ;
struct sti_hda {int dummy; } ;

/* Variables and functions */
 unsigned int AWG_MAX_INST ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 scalar_t__ HDA_SYNC_AWGI ; 
 int /*<<< orphan*/  hda_write (struct sti_hda*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sti_hda_configure_awg(struct sti_hda *hda, u32 *awg_instr, int nb)
{
	unsigned int i;

	DRM_DEBUG_DRIVER("\n");

	for (i = 0; i < nb; i++)
		hda_write(hda, awg_instr[i], HDA_SYNC_AWGI + i * 4);
	for (i = nb; i < AWG_MAX_INST; i++)
		hda_write(hda, 0, HDA_SYNC_AWGI + i * 4);
}