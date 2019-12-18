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
typedef  int /*<<< orphan*/  u16 ;
struct ks_wlan_private {int dummy; } ;
struct hostif_mic_failure_request {void* timer; void* failure_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIF_MIC_FAILURE_REQ ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hif_align_size (int) ; 
 struct hostif_mic_failure_request* hostif_generic_request (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_request_to_device (struct ks_wlan_private*,struct hostif_mic_failure_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void hostif_mic_failure_request(struct ks_wlan_private *priv,
				u16 failure_count, u16 timer)
{
	struct hostif_mic_failure_request *pp;

	pp = hostif_generic_request(sizeof(*pp), HIF_MIC_FAILURE_REQ);
	if (!pp)
		return;

	pp->failure_count = cpu_to_le16(failure_count);
	pp->timer = cpu_to_le16(timer);

	send_request_to_device(priv, pp, hif_align_size(sizeof(*pp)));
}