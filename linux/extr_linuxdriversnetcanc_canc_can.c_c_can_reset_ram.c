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
struct c_can_priv {int /*<<< orphan*/  (* raminit ) (struct c_can_priv const*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct c_can_priv const*,int) ; 

__attribute__((used)) static inline void c_can_reset_ram(const struct c_can_priv *priv, bool enable)
{
	if (priv->raminit)
		priv->raminit(priv, enable);
}