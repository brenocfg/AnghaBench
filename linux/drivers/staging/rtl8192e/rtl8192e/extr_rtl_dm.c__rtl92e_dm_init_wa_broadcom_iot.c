#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rt_hi_throughput {int bWAIotBroadcom; int /*<<< orphan*/  WAIotTH; } ;
struct r8192_priv {TYPE_1__* rtllib; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct rt_hi_throughput* pHTInfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  WAIotTHVal ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_dm_init_wa_broadcom_iot(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv((struct net_device *)dev);
	struct rt_hi_throughput *pHTInfo = priv->rtllib->pHTInfo;

	pHTInfo->bWAIotBroadcom = false;
	pHTInfo->WAIotTH = WAIotTHVal;
}