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
struct smscore_device_t {int (* sendrequest_handler ) (int /*<<< orphan*/ ,void*,size_t) ;int /*<<< orphan*/  context; } ;
struct smscore_client_t {struct smscore_device_t* coredev; } ;
struct sms_msg_hdr {int /*<<< orphan*/  msg_src_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int smscore_validate_client (struct smscore_device_t*,struct smscore_client_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,void*,size_t) ; 

int smsclient_sendrequest(struct smscore_client_t *client,
			  void *buffer, size_t size)
{
	struct smscore_device_t *coredev;
	struct sms_msg_hdr *phdr = (struct sms_msg_hdr *) buffer;
	int rc;

	if (!client) {
		pr_err("Got NULL client\n");
		return -EINVAL;
	}

	coredev = client->coredev;

	/* check that no other channel with same id exists */
	if (!coredev) {
		pr_err("Got NULL coredev\n");
		return -EINVAL;
	}

	rc = smscore_validate_client(client->coredev, client, 0,
				     phdr->msg_src_id);
	if (rc < 0)
		return rc;

	return coredev->sendrequest_handler(coredev->context, buffer, size);
}