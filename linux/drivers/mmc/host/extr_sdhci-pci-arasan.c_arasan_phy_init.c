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
typedef  int u8 ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALDONE_MASK ; 
 int /*<<< orphan*/  CLKBUF_SEL ; 
 int /*<<< orphan*/  CLK_CTRL ; 
 int /*<<< orphan*/  CMD_CTRL ; 
 int /*<<< orphan*/  DATA_CTRL ; 
 int EBUSY ; 
 int /*<<< orphan*/  IOPU_CTRL1 ; 
 int /*<<< orphan*/  IOPU_CTRL2 ; 
 int /*<<< orphan*/  IOREN_CTRL1 ; 
 int /*<<< orphan*/  IOREN_CTRL2 ; 
 int /*<<< orphan*/  IPAD_CTRL1 ; 
 int /*<<< orphan*/  IPAD_CTRL2 ; 
 int /*<<< orphan*/  IPAD_STS ; 
 int LEGACY_MODE ; 
 int MAX_CLK_BUF ; 
 int /*<<< orphan*/  MODE_CTRL ; 
 int PDB_CLOCK ; 
 int PDB_CMND ; 
 int PDB_DATA ; 
 int PDB_ENBL ; 
 int PDB_STRB ; 
 int PU_CMD ; 
 int PU_DAT ; 
 int REN_CMND ; 
 int REN_DATA ; 
 int REN_STRB ; 
 int RETB_ENBL ; 
 int RTRIM_EN ; 
 int /*<<< orphan*/  STRB_CTRL ; 
 scalar_t__ arasan_phy_read (struct sdhci_host*,int /*<<< orphan*/ ,int*) ; 
 int arasan_phy_sts_poll (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ arasan_phy_write (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arasan_phy_init(struct sdhci_host *host)
{
	int ret;
	u8 val;

	/* Program IOPADs and wait for calibration to be done */
	if (arasan_phy_read(host, IPAD_CTRL1, &val) ||
	    arasan_phy_write(host, val | RETB_ENBL | PDB_ENBL, IPAD_CTRL1) ||
	    arasan_phy_read(host, IPAD_CTRL2, &val) ||
	    arasan_phy_write(host, val | RTRIM_EN, IPAD_CTRL2))
		return -EBUSY;
	ret = arasan_phy_sts_poll(host, IPAD_STS, CALDONE_MASK);
	if (ret)
		return -EBUSY;

	/* Program CMD/Data lines */
	if (arasan_phy_read(host, IOREN_CTRL1, &val) ||
	    arasan_phy_write(host, val | REN_CMND | REN_STRB, IOREN_CTRL1) ||
	    arasan_phy_read(host, IOPU_CTRL1, &val) ||
	    arasan_phy_write(host, val | PU_CMD, IOPU_CTRL1) ||
	    arasan_phy_read(host, CMD_CTRL, &val) ||
	    arasan_phy_write(host, val | PDB_CMND, CMD_CTRL) ||
	    arasan_phy_read(host, IOREN_CTRL2, &val) ||
	    arasan_phy_write(host, val | REN_DATA, IOREN_CTRL2) ||
	    arasan_phy_read(host, IOPU_CTRL2, &val) ||
	    arasan_phy_write(host, val | PU_DAT, IOPU_CTRL2) ||
	    arasan_phy_read(host, DATA_CTRL, &val) ||
	    arasan_phy_write(host, val | PDB_DATA, DATA_CTRL) ||
	    arasan_phy_read(host, STRB_CTRL, &val) ||
	    arasan_phy_write(host, val | PDB_STRB, STRB_CTRL) ||
	    arasan_phy_read(host, CLK_CTRL, &val) ||
	    arasan_phy_write(host, val | PDB_CLOCK, CLK_CTRL) ||
	    arasan_phy_read(host, CLKBUF_SEL, &val) ||
	    arasan_phy_write(host, val | MAX_CLK_BUF, CLKBUF_SEL) ||
	    arasan_phy_write(host, LEGACY_MODE, MODE_CTRL))
		return -EBUSY;
	return 0;
}