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
struct usbhsh_request {int dummy; } ;
struct usbhsh_hpriv {int dummy; } ;
struct usbhs_priv {int dummy; } ;
struct usbhs_pkt {int dummy; } ;

/* Variables and functions */
 struct usbhsh_request* usbhsh_pkt_to_ureq (struct usbhs_pkt*) ; 
 struct usbhsh_hpriv* usbhsh_priv_to_hpriv (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhsh_ureq_free (struct usbhsh_hpriv*,struct usbhsh_request*) ; 

__attribute__((used)) static void usbhsh_data_stage_packet_done(struct usbhs_priv *priv,
					  struct usbhs_pkt *pkt)
{
	struct usbhsh_request *ureq = usbhsh_pkt_to_ureq(pkt);
	struct usbhsh_hpriv *hpriv = usbhsh_priv_to_hpriv(priv);

	/* this ureq was connected to urb when usbhsh_urb_enqueue()  */

	usbhsh_ureq_free(hpriv, ureq);
}