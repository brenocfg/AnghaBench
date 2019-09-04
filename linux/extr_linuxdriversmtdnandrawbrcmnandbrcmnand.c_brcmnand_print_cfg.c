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
struct brcmnand_host {int /*<<< orphan*/  ctrl; } ;
struct brcmnand_cfg {int block_size; int page_size; int ecc_level; scalar_t__ sector_size_1k; int /*<<< orphan*/  device_width; int /*<<< orphan*/  spare_area_size; scalar_t__ device_size; } ;

/* Variables and functions */
 scalar_t__ is_hamming_ecc (int /*<<< orphan*/ ,struct brcmnand_cfg*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static void brcmnand_print_cfg(struct brcmnand_host *host,
			       char *buf, struct brcmnand_cfg *cfg)
{
	buf += sprintf(buf,
		"%lluMiB total, %uKiB blocks, %u%s pages, %uB OOB, %u-bit",
		(unsigned long long)cfg->device_size >> 20,
		cfg->block_size >> 10,
		cfg->page_size >= 1024 ? cfg->page_size >> 10 : cfg->page_size,
		cfg->page_size >= 1024 ? "KiB" : "B",
		cfg->spare_area_size, cfg->device_width);

	/* Account for Hamming ECC and for BCH 512B vs 1KiB sectors */
	if (is_hamming_ecc(host->ctrl, cfg))
		sprintf(buf, ", Hamming ECC");
	else if (cfg->sector_size_1k)
		sprintf(buf, ", BCH-%u (1KiB sector)", cfg->ecc_level << 1);
	else
		sprintf(buf, ", BCH-%u", cfg->ecc_level);
}