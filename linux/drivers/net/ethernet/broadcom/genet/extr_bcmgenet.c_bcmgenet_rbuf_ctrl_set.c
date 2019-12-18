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
struct bcmgenet_priv {int dummy; } ;

/* Variables and functions */
 scalar_t__ GENET_IS_V1 (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  RBUF_FLUSH_CTRL_V1 ; 
 int /*<<< orphan*/  SYS_RBUF_FLUSH_CTRL ; 
 int /*<<< orphan*/  bcmgenet_rbuf_writel (struct bcmgenet_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_sys_writel (struct bcmgenet_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bcmgenet_rbuf_ctrl_set(struct bcmgenet_priv *priv, u32 val)
{
	if (GENET_IS_V1(priv))
		bcmgenet_rbuf_writel(priv, val, RBUF_FLUSH_CTRL_V1);
	else
		bcmgenet_sys_writel(priv, val, SYS_RBUF_FLUSH_CTRL);
}