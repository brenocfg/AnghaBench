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
struct c_can_priv {int /*<<< orphan*/  (* read_reg ) (struct c_can_priv*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  C_CAN_NEWDAT1_REG ; 
 int /*<<< orphan*/  stub1 (struct c_can_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 c_can_get_pending(struct c_can_priv *priv)
{
	u32 pend = priv->read_reg(priv, C_CAN_NEWDAT1_REG);

	return pend;
}