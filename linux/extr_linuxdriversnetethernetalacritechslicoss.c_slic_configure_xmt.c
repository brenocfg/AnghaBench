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
struct slic_device {scalar_t__ duplex; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int SLIC_GXCR_PAUSEEN ; 
 int SLIC_GXCR_RESET ; 
 int SLIC_GXCR_XMTEN ; 
 int /*<<< orphan*/  SLIC_REG_WXCFG ; 
 int /*<<< orphan*/  slic_write (struct slic_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void slic_configure_xmt(struct slic_device *sdev)
{
	u32 val;

	val = SLIC_GXCR_RESET | SLIC_GXCR_XMTEN;

	if (sdev->duplex == DUPLEX_FULL)
		val |= SLIC_GXCR_PAUSEEN;

	slic_write(sdev, SLIC_REG_WXCFG, val);
}