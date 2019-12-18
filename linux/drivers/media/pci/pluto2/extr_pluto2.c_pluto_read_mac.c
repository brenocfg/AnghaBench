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
typedef  int u8 ;
typedef  int u32 ;
struct pluto {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_IMAC ; 
 int /*<<< orphan*/  REG_LMAC ; 
 int /*<<< orphan*/  REG_MMAC ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int*) ; 
 int pluto_readreg (struct pluto*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pluto_read_mac(struct pluto *pluto, u8 *mac)
{
	u32 val = pluto_readreg(pluto, REG_MMAC);
	mac[0] = (val >> 8) & 0xff;
	mac[1] = (val >> 0) & 0xff;

	val = pluto_readreg(pluto, REG_IMAC);
	mac[2] = (val >> 8) & 0xff;
	mac[3] = (val >> 0) & 0xff;

	val = pluto_readreg(pluto, REG_LMAC);
	mac[4] = (val >> 8) & 0xff;
	mac[5] = (val >> 0) & 0xff;

	dev_info(&pluto->pdev->dev, "MAC %pM\n", mac);
}