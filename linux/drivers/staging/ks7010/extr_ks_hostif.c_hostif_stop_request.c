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
struct ks_wlan_private {int dummy; } ;
struct hostif_stop_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIF_STOP_REQ ; 
 int /*<<< orphan*/  hif_align_size (int) ; 
 struct hostif_stop_request* hostif_generic_request (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_request_to_device (struct ks_wlan_private*,struct hostif_stop_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void hostif_stop_request(struct ks_wlan_private *priv)
{
	struct hostif_stop_request *pp;

	pp = hostif_generic_request(sizeof(*pp), HIF_STOP_REQ);
	if (!pp)
		return;

	send_request_to_device(priv, pp, hif_align_size(sizeof(*pp)));
}