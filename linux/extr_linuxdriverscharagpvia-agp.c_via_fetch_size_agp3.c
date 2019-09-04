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
typedef  int u16 ;
struct aper_size_info_16 {int size_value; int size; } ;
struct TYPE_4__ {int aperture_size_idx; void* current_size; void* previous_size; TYPE_1__* driver; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int num_aperture_sizes; int /*<<< orphan*/  aperture_sizes; } ;

/* Variables and functions */
 struct aper_size_info_16* A_SIZE_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIA_AGP3_APSIZE ; 
 TYPE_2__* agp_bridge ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int via_fetch_size_agp3(void)
{
	int i;
	u16 temp;
	struct aper_size_info_16 *values;

	values = A_SIZE_16(agp_bridge->driver->aperture_sizes);
	pci_read_config_word(agp_bridge->dev, VIA_AGP3_APSIZE, &temp);
	temp &= 0xfff;

	for (i = 0; i < agp_bridge->driver->num_aperture_sizes; i++) {
		if (temp == values[i].size_value) {
			agp_bridge->previous_size =
				agp_bridge->current_size = (void *) (values + i);
			agp_bridge->aperture_size_idx = i;
			return values[i].size;
		}
	}
	return 0;
}