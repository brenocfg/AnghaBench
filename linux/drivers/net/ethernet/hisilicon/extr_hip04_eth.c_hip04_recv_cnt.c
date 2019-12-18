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
struct hip04_priv {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ PPE_HIS_RX_PKT_CNT ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static u32 hip04_recv_cnt(struct hip04_priv *priv)
{
	return readl(priv->base + PPE_HIS_RX_PKT_CNT);
}