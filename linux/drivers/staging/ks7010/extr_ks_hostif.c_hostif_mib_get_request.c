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
struct ks_wlan_private {int dummy; } ;
struct hostif_mib_get_request {int /*<<< orphan*/  mib_attribute; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIF_MIB_GET_REQ ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hif_align_size (int) ; 
 struct hostif_mib_get_request* hostif_generic_request (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_request_to_device (struct ks_wlan_private*,struct hostif_mib_get_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hostif_mib_get_request(struct ks_wlan_private *priv,
				   u32 mib_attribute)
{
	struct hostif_mib_get_request *pp;

	pp = hostif_generic_request(sizeof(*pp), HIF_MIB_GET_REQ);
	if (!pp)
		return;

	pp->mib_attribute = cpu_to_le32(mib_attribute);

	send_request_to_device(priv, pp, hif_align_size(sizeof(*pp)));
}