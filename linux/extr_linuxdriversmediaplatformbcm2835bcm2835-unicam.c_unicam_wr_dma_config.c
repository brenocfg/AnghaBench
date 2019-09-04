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
struct unicam_device {int /*<<< orphan*/  cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNICAM_IBLS ; 
 int /*<<< orphan*/  reg_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void unicam_wr_dma_config(struct unicam_device *dev,
				 unsigned int stride)
{
	reg_write(&dev->cfg, UNICAM_IBLS, stride);
}