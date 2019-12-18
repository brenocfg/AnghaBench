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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmw_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVGA_REG_BUSY ; 
 scalar_t__ vmw_read (struct vmw_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool vmw_fifo_idle(struct vmw_private *dev_priv, uint32_t seqno)
{

	return (vmw_read(dev_priv, SVGA_REG_BUSY) == 0);
}