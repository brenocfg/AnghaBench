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
struct tegra_plane {unsigned int offset; TYPE_1__* dc; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_WARN (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static inline unsigned int tegra_plane_offset(struct tegra_plane *plane,
					      unsigned int offset)
{
	if (offset >= 0x500 && offset <= 0x638) {
		offset = 0x000 + (offset - 0x500);
		return plane->offset + offset;
	}

	if (offset >= 0x700 && offset <= 0x719) {
		offset = 0x180 + (offset - 0x700);
		return plane->offset + offset;
	}

	if (offset >= 0x800 && offset <= 0x839) {
		offset = 0x1c0 + (offset - 0x800);
		return plane->offset + offset;
	}

	dev_WARN(plane->dc->dev, "invalid offset: %x\n", offset);

	return plane->offset + offset;
}