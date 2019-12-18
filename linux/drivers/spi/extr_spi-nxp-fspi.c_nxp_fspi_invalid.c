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
struct nxp_fspi {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ FSPI_MCR0 ; 
 int FSPI_MCR0_SWRST ; 
 int /*<<< orphan*/  POLL_TOUT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int fspi_readl (struct nxp_fspi*,scalar_t__) ; 
 int fspi_readl_poll_tout (struct nxp_fspi*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fspi_writel (struct nxp_fspi*,int,scalar_t__) ; 

__attribute__((used)) static inline void nxp_fspi_invalid(struct nxp_fspi *f)
{
	u32 reg;
	int ret;

	reg = fspi_readl(f, f->iobase + FSPI_MCR0);
	fspi_writel(f, reg | FSPI_MCR0_SWRST, f->iobase + FSPI_MCR0);

	/* w1c register, wait unit clear */
	ret = fspi_readl_poll_tout(f, f->iobase + FSPI_MCR0,
				   FSPI_MCR0_SWRST, 0, POLL_TOUT, false);
	WARN_ON(ret);
}