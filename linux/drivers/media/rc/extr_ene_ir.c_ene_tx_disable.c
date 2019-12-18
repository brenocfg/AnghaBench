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
struct ene_device {int /*<<< orphan*/ * tx_buffer; int /*<<< orphan*/  saved_conf1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENE_CIRCFG ; 
 int /*<<< orphan*/  ene_write_reg (struct ene_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ene_tx_disable(struct ene_device *dev)
{
	ene_write_reg(dev, ENE_CIRCFG, dev->saved_conf1);
	dev->tx_buffer = NULL;
}