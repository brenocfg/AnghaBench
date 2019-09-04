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
struct enc28j60_net {int hw_enable; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECON1 ; 
 int /*<<< orphan*/  ECON1_RXEN ; 
 int /*<<< orphan*/  EIE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nolock_reg_bfclr (struct enc28j60_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nolock_regb_write (struct enc28j60_net*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void enc28j60_hw_disable(struct enc28j60_net *priv)
{
	mutex_lock(&priv->lock);
	/* disable interrutps and packet reception */
	nolock_regb_write(priv, EIE, 0x00);
	nolock_reg_bfclr(priv, ECON1, ECON1_RXEN);
	priv->hw_enable = false;
	mutex_unlock(&priv->lock);
}