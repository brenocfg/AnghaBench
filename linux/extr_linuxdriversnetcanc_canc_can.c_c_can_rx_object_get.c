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
struct net_device {int dummy; } ;
struct c_can_priv {int /*<<< orphan*/  comm_rcv_high; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_RX ; 
 int /*<<< orphan*/  c_can_object_get (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void c_can_rx_object_get(struct net_device *dev,
				       struct c_can_priv *priv, u32 obj)
{
		c_can_object_get(dev, IF_RX, obj, priv->comm_rcv_high);
}