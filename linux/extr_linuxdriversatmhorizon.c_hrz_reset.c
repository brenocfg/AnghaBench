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
typedef  int /*<<< orphan*/  hrz_dev ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_0_REG ; 
 int RESET_ATM ; 
 int RESET_HORIZON ; 
 int RESET_HOST ; 
 int RESET_RX ; 
 int RESET_TX ; 
 int rd_regl (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wr_regl (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hrz_reset (const hrz_dev * dev) {
  u32 control_0_reg = rd_regl (dev, CONTROL_0_REG);
  
  // why not set RESET_HORIZON to one and wait for the card to
  // reassert that bit as zero? Like so:
  control_0_reg = control_0_reg & RESET_HORIZON;
  wr_regl (dev, CONTROL_0_REG, control_0_reg);
  while (control_0_reg & RESET_HORIZON)
    control_0_reg = rd_regl (dev, CONTROL_0_REG);
  
  // old reset code retained:
  wr_regl (dev, CONTROL_0_REG, control_0_reg |
	   RESET_ATM | RESET_RX | RESET_TX | RESET_HOST);
  // just guessing here
  udelay (1000);
  
  wr_regl (dev, CONTROL_0_REG, control_0_reg);
}