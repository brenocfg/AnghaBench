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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  GPMC_CONFIG7_CSVALID ; 
 int /*<<< orphan*/  GPMC_CS_CONFIG7 ; 
 int /*<<< orphan*/  gpmc_cs_read_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpmc_cs_write_reg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpmc_cs_enable_mem(int cs)
{
	u32 l;

	l = gpmc_cs_read_reg(cs, GPMC_CS_CONFIG7);
	l |= GPMC_CONFIG7_CSVALID;
	gpmc_cs_write_reg(cs, GPMC_CS_CONFIG7, l);
}