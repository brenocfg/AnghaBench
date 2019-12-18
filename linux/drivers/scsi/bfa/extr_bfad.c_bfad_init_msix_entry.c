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
struct msix_entry {int entry; } ;
struct bfad_s {size_t nvec; TYPE_2__* msix_tab; } ;
struct TYPE_3__ {int entry; } ;
struct TYPE_4__ {struct bfad_s* bfad; TYPE_1__ msix; } ;

/* Variables and functions */
 int MAX_MSIX_ENTRY ; 

__attribute__((used)) static void
bfad_init_msix_entry(struct bfad_s *bfad, struct msix_entry *msix_entries,
			 int mask, int max_bit)
{
	int	i;
	int	match = 0x00000001;

	for (i = 0, bfad->nvec = 0; i < MAX_MSIX_ENTRY; i++) {
		if (mask & match) {
			bfad->msix_tab[bfad->nvec].msix.entry = i;
			bfad->msix_tab[bfad->nvec].bfad = bfad;
			msix_entries[bfad->nvec].entry = i;
			bfad->nvec++;
		}

		match <<= 1;
	}

}