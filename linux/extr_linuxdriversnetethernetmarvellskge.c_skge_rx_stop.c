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
struct skge_hw {int dummy; } ;

/* Variables and functions */
 int CSR_SET_RESET ; 
 int /*<<< orphan*/  CSR_STOP ; 
 int /*<<< orphan*/  Q_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_CSR ; 
 int /*<<< orphan*/  Q_R1 ; 
 int /*<<< orphan*/  Q_R2 ; 
 int /*<<< orphan*/  RB_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_CTRL ; 
 int RB_DIS_OP_MD ; 
 int RB_RST_SET ; 
 int /*<<< orphan*/ * rxqaddr ; 
 int /*<<< orphan*/  skge_write32 (struct skge_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skge_write8 (struct skge_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skge_rx_stop(struct skge_hw *hw, int port)
{
	skge_write8(hw, Q_ADDR(rxqaddr[port], Q_CSR), CSR_STOP);
	skge_write32(hw, RB_ADDR(port ? Q_R2 : Q_R1, RB_CTRL),
		     RB_RST_SET|RB_DIS_OP_MD);
	skge_write32(hw, Q_ADDR(rxqaddr[port], Q_CSR), CSR_SET_RESET);
}