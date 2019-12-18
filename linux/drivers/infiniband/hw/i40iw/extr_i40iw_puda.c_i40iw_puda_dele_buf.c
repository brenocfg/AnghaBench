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
struct i40iw_sc_dev {int /*<<< orphan*/  hw; } ;
struct i40iw_puda_buf {int /*<<< orphan*/  buf_mem; int /*<<< orphan*/  mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40iw_free_dma_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_free_virt_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i40iw_puda_dele_buf(struct i40iw_sc_dev *dev,
				struct i40iw_puda_buf *buf)
{
	i40iw_free_dma_mem(dev->hw, &buf->mem);
	i40iw_free_virt_mem(dev->hw, &buf->buf_mem);
}