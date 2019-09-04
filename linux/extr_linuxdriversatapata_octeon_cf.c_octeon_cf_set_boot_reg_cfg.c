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
struct TYPE_2__ {unsigned int tim_mult; int en; scalar_t__ ale; scalar_t__ orbit; scalar_t__ oe_ext; scalar_t__ we_ext; scalar_t__ sam; scalar_t__ rd_dly; scalar_t__ dmack; } ;
union cvmx_mio_boot_reg_cfgx {int /*<<< orphan*/  u64; TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_MIO_BOOT_REG_CFGX (int) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void octeon_cf_set_boot_reg_cfg(int cs, unsigned int multiplier)
{
	union cvmx_mio_boot_reg_cfgx reg_cfg;
	unsigned int tim_mult;

	switch (multiplier) {
	case 8:
		tim_mult = 3;
		break;
	case 4:
		tim_mult = 0;
		break;
	case 2:
		tim_mult = 2;
		break;
	default:
		tim_mult = 1;
		break;
	}

	reg_cfg.u64 = cvmx_read_csr(CVMX_MIO_BOOT_REG_CFGX(cs));
	reg_cfg.s.dmack = 0;	/* Don't assert DMACK on access */
	reg_cfg.s.tim_mult = tim_mult;	/* Timing mutiplier */
	reg_cfg.s.rd_dly = 0;	/* Sample on falling edge of BOOT_OE */
	reg_cfg.s.sam = 0;	/* Don't combine write and output enable */
	reg_cfg.s.we_ext = 0;	/* No write enable extension */
	reg_cfg.s.oe_ext = 0;	/* No read enable extension */
	reg_cfg.s.en = 1;	/* Enable this region */
	reg_cfg.s.orbit = 0;	/* Don't combine with previous region */
	reg_cfg.s.ale = 0;	/* Don't do address multiplexing */
	cvmx_write_csr(CVMX_MIO_BOOT_REG_CFGX(cs), reg_cfg.u64);
}