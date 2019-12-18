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
struct ibmvfc_host {int client_migrated; int /*<<< orphan*/  dev; int /*<<< orphan*/  pool; int /*<<< orphan*/  logged_in; int /*<<< orphan*/  state; } ;
struct ibmvfc_event {int /*<<< orphan*/  (* done ) (struct ibmvfc_event*) ;int /*<<< orphan*/  queue; int /*<<< orphan*/  timer; int /*<<< orphan*/  free; } ;
struct ibmvfc_crq {long ioba; int valid; long format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_ERROR ; 
 int /*<<< orphan*/  DID_REQUEUE ; 
 scalar_t__ IBMVFC_ASYNC_EVENT ; 
#define  IBMVFC_CRQ_CMD_RSP 132 
#define  IBMVFC_CRQ_INIT 131 
#define  IBMVFC_CRQ_INIT_COMPLETE 130 
#define  IBMVFC_CRQ_INIT_RSP 129 
#define  IBMVFC_CRQ_XPORT_EVENT 128 
 int /*<<< orphan*/  IBMVFC_HOST_ACTION_NONE ; 
 int /*<<< orphan*/  IBMVFC_HOST_ACTION_REENABLE ; 
 int /*<<< orphan*/  IBMVFC_HOST_ACTION_RESET ; 
 int /*<<< orphan*/  IBMVFC_LINK_DOWN ; 
 int /*<<< orphan*/  IBMVFC_NO_CRQ ; 
 long IBMVFC_PARTITION_MIGRATED ; 
 long IBMVFC_PARTNER_DEREGISTER ; 
 long IBMVFC_PARTNER_FAILED ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ be64_to_cpu (long) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ibmvfc_init_host (struct ibmvfc_host*) ; 
 int /*<<< orphan*/  ibmvfc_link_down (struct ibmvfc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_purge_requests (struct ibmvfc_host*,int /*<<< orphan*/ ) ; 
 long ibmvfc_send_crq_init_complete (struct ibmvfc_host*) ; 
 int /*<<< orphan*/  ibmvfc_set_host_action (struct ibmvfc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_trc_end (struct ibmvfc_event*) ; 
 int /*<<< orphan*/  ibmvfc_valid_event (int /*<<< orphan*/ *,struct ibmvfc_event*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ibmvfc_event*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ibmvfc_handle_crq(struct ibmvfc_crq *crq, struct ibmvfc_host *vhost)
{
	long rc;
	struct ibmvfc_event *evt = (struct ibmvfc_event *)be64_to_cpu(crq->ioba);

	switch (crq->valid) {
	case IBMVFC_CRQ_INIT_RSP:
		switch (crq->format) {
		case IBMVFC_CRQ_INIT:
			dev_info(vhost->dev, "Partner initialized\n");
			/* Send back a response */
			rc = ibmvfc_send_crq_init_complete(vhost);
			if (rc == 0)
				ibmvfc_init_host(vhost);
			else
				dev_err(vhost->dev, "Unable to send init rsp. rc=%ld\n", rc);
			break;
		case IBMVFC_CRQ_INIT_COMPLETE:
			dev_info(vhost->dev, "Partner initialization complete\n");
			ibmvfc_init_host(vhost);
			break;
		default:
			dev_err(vhost->dev, "Unknown crq message type: %d\n", crq->format);
		}
		return;
	case IBMVFC_CRQ_XPORT_EVENT:
		vhost->state = IBMVFC_NO_CRQ;
		vhost->logged_in = 0;
		ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_NONE);
		if (crq->format == IBMVFC_PARTITION_MIGRATED) {
			/* We need to re-setup the interpartition connection */
			dev_info(vhost->dev, "Partition migrated, Re-enabling adapter\n");
			vhost->client_migrated = 1;
			ibmvfc_purge_requests(vhost, DID_REQUEUE);
			ibmvfc_link_down(vhost, IBMVFC_LINK_DOWN);
			ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_REENABLE);
		} else if (crq->format == IBMVFC_PARTNER_FAILED || crq->format == IBMVFC_PARTNER_DEREGISTER) {
			dev_err(vhost->dev, "Host partner adapter deregistered or failed (rc=%d)\n", crq->format);
			ibmvfc_purge_requests(vhost, DID_ERROR);
			ibmvfc_link_down(vhost, IBMVFC_LINK_DOWN);
			ibmvfc_set_host_action(vhost, IBMVFC_HOST_ACTION_RESET);
		} else {
			dev_err(vhost->dev, "Received unknown transport event from partner (rc=%d)\n", crq->format);
		}
		return;
	case IBMVFC_CRQ_CMD_RSP:
		break;
	default:
		dev_err(vhost->dev, "Got an invalid message type 0x%02x\n", crq->valid);
		return;
	}

	if (crq->format == IBMVFC_ASYNC_EVENT)
		return;

	/* The only kind of payload CRQs we should get are responses to
	 * things we send. Make sure this response is to something we
	 * actually sent
	 */
	if (unlikely(!ibmvfc_valid_event(&vhost->pool, evt))) {
		dev_err(vhost->dev, "Returned correlation_token 0x%08llx is invalid!\n",
			crq->ioba);
		return;
	}

	if (unlikely(atomic_read(&evt->free))) {
		dev_err(vhost->dev, "Received duplicate correlation_token 0x%08llx!\n",
			crq->ioba);
		return;
	}

	del_timer(&evt->timer);
	list_del(&evt->queue);
	ibmvfc_trc_end(evt);
	evt->done(evt);
}