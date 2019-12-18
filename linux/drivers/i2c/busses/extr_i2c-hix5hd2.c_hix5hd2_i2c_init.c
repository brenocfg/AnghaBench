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
struct hix5hd2_i2c_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hix5hd2_i2c_clr_all_irq (struct hix5hd2_i2c_priv*) ; 
 int /*<<< orphan*/  hix5hd2_i2c_disable_irq (struct hix5hd2_i2c_priv*) ; 
 int /*<<< orphan*/  hix5hd2_i2c_drv_setrate (struct hix5hd2_i2c_priv*) ; 
 int /*<<< orphan*/  hix5hd2_i2c_enable_irq (struct hix5hd2_i2c_priv*) ; 

__attribute__((used)) static void hix5hd2_i2c_init(struct hix5hd2_i2c_priv *priv)
{
	hix5hd2_i2c_disable_irq(priv);
	hix5hd2_i2c_drv_setrate(priv);
	hix5hd2_i2c_clr_all_irq(priv);
	hix5hd2_i2c_enable_irq(priv);
}