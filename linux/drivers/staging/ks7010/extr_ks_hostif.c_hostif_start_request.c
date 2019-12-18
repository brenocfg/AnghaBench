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
struct TYPE_2__ {scalar_t__ size; } ;
struct ks_wlan_private {scalar_t__ scan_ind_count; TYPE_1__ aplist; } ;
struct hostif_start_request {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIF_START_REQ ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned char) ; 
 int /*<<< orphan*/  hif_align_size (int) ; 
 struct hostif_start_request* hostif_generic_request (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_request_to_device (struct ks_wlan_private*,struct hostif_start_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void hostif_start_request(struct ks_wlan_private *priv, unsigned char mode)
{
	struct hostif_start_request *pp;

	pp = hostif_generic_request(sizeof(*pp), HIF_START_REQ);
	if (!pp)
		return;

	pp->mode = cpu_to_le16(mode);

	send_request_to_device(priv, pp, hif_align_size(sizeof(*pp)));

	priv->aplist.size = 0;
	priv->scan_ind_count = 0;
}