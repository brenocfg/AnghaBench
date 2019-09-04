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
struct virtio_crypto_request {int /*<<< orphan*/  sgs; int /*<<< orphan*/  req_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ ) ; 

void
virtcrypto_clear_request(struct virtio_crypto_request *vc_req)
{
	if (vc_req) {
		kzfree(vc_req->req_data);
		kfree(vc_req->sgs);
	}
}