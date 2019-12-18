#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/ * body; } ;
struct TYPE_6__ {TYPE_2__ rate_set; int /*<<< orphan*/  scan_type; int /*<<< orphan*/  cts_mode; int /*<<< orphan*/  phy_type; } ;
struct ks_wlan_private {TYPE_3__ reg; } ;
struct TYPE_4__ {int /*<<< orphan*/ * body; int /*<<< orphan*/  size; } ;
struct hostif_request {TYPE_1__ rate_set; int /*<<< orphan*/  capability; void* scan_type; void* cts_mode; void* phy_type; } ;

/* Variables and functions */
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_wlan_cap (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_request(struct ks_wlan_private *priv,
			 struct hostif_request *req)
{
	req->phy_type = cpu_to_le16(priv->reg.phy_type);
	req->cts_mode = cpu_to_le16(priv->reg.cts_mode);
	req->scan_type = cpu_to_le16(priv->reg.scan_type);
	req->rate_set.size = priv->reg.rate_set.size;
	req->capability = ks_wlan_cap(priv);
	memcpy(&req->rate_set.body[0], &priv->reg.rate_set.body[0],
	       priv->reg.rate_set.size);
}