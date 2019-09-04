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
typedef  int u16 ;
struct TYPE_2__ {int revision; } ;
struct bcma_bus {TYPE_1__ sprom; } ;

/* Variables and functions */
 int ENOENT ; 
 int const SSB_SPROM_REVISION_REV ; 
 int /*<<< orphan*/  bcma_debug (struct bcma_bus*,char*,int) ; 
 int bcma_sprom_check_crc (int const*,size_t) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int bcma_sprom_valid(struct bcma_bus *bus, const u16 *sprom,
			    size_t words)
{
	u16 revision;
	int err;

	err = bcma_sprom_check_crc(sprom, words);
	if (err)
		return err;

	revision = sprom[words - 1] & SSB_SPROM_REVISION_REV;
	if (revision != 8 && revision != 9 && revision != 10) {
		pr_err("Unsupported SPROM revision: %d\n", revision);
		return -ENOENT;
	}

	bus->sprom.revision = revision;
	bcma_debug(bus, "Found SPROM revision %d\n", revision);

	return 0;
}