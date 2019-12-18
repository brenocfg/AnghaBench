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
typedef  size_t u8 ;
struct ib_sa_query {int flags; struct ib_sa_client* client; TYPE_3__* mad_buf; int /*<<< orphan*/  release; int /*<<< orphan*/ * callback; struct ib_sa_port* port; } ;
struct sa_path_rec {scalar_t__ rec_type; void (* callback ) (int,struct sa_path_rec*,void*) ;struct sa_path_rec* conv_pr; struct ib_sa_query sa_query; void* context; } ;
struct ib_sa_port {struct ib_mad_agent* agent; } ;
struct ib_sa_path_query {scalar_t__ rec_type; void (* callback ) (int,struct sa_path_rec*,void*) ;struct ib_sa_path_query* conv_pr; struct ib_sa_query sa_query; void* context; } ;
struct TYPE_5__ {int /*<<< orphan*/  comp_mask; } ;
struct TYPE_4__ {int /*<<< orphan*/  attr_id; int /*<<< orphan*/  method; } ;
struct ib_sa_mad {int /*<<< orphan*/  data; TYPE_2__ sa_hdr; TYPE_1__ mad_hdr; } ;
struct ib_sa_device {size_t start_port; struct ib_sa_port* port; } ;
struct ib_sa_client {int dummy; } ;
struct ib_mad_agent {int dummy; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  ib_sa_comp_mask ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum opa_pr_supported { ____Placeholder_opa_pr_supported } opa_pr_supported ;
struct TYPE_6__ {struct sa_path_rec** context; struct ib_sa_mad* mad; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IB_MGMT_METHOD_GET ; 
 int /*<<< orphan*/  IB_SA_ATTR_PATH_REC ; 
 int IB_SA_ENABLE_LOCAL_SERVICE ; 
 int IB_SA_QUERY_OPA ; 
 int PR_NOT_SUPPORTED ; 
 int PR_OPA_SUPPORTED ; 
 scalar_t__ SA_PATH_REC_TYPE_IB ; 
 scalar_t__ SA_PATH_REC_TYPE_OPA ; 
 int alloc_mad (struct ib_sa_query*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_mad (struct ib_sa_query*) ; 
 struct ib_sa_device* ib_get_client_data (struct ib_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_pack (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sa_path_rec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_sa_client_get (struct ib_sa_client*) ; 
 int /*<<< orphan*/  ib_sa_client_put (struct ib_sa_client*) ; 
 int /*<<< orphan*/ * ib_sa_path_rec_callback ; 
 int /*<<< orphan*/  ib_sa_path_rec_release ; 
 int /*<<< orphan*/  init_mad (struct ib_sa_query*,struct ib_mad_agent*) ; 
 int /*<<< orphan*/  kfree (struct sa_path_rec*) ; 
 struct sa_path_rec* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct sa_path_rec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opa_path_rec_table ; 
 int opa_pr_query_possible (struct ib_sa_client*,struct ib_device*,size_t,struct sa_path_rec*) ; 
 int /*<<< orphan*/  path_rec_table ; 
 int /*<<< orphan*/  sa_client ; 
 int /*<<< orphan*/  sa_convert_path_opa_to_ib (struct sa_path_rec*,struct sa_path_rec*) ; 
 int send_mad (struct ib_sa_query*,unsigned long,int /*<<< orphan*/ ) ; 

int ib_sa_path_rec_get(struct ib_sa_client *client,
		       struct ib_device *device, u8 port_num,
		       struct sa_path_rec *rec,
		       ib_sa_comp_mask comp_mask,
		       unsigned long timeout_ms, gfp_t gfp_mask,
		       void (*callback)(int status,
					struct sa_path_rec *resp,
					void *context),
		       void *context,
		       struct ib_sa_query **sa_query)
{
	struct ib_sa_path_query *query;
	struct ib_sa_device *sa_dev = ib_get_client_data(device, &sa_client);
	struct ib_sa_port   *port;
	struct ib_mad_agent *agent;
	struct ib_sa_mad *mad;
	enum opa_pr_supported status;
	int ret;

	if (!sa_dev)
		return -ENODEV;

	if ((rec->rec_type != SA_PATH_REC_TYPE_IB) &&
	    (rec->rec_type != SA_PATH_REC_TYPE_OPA))
		return -EINVAL;

	port  = &sa_dev->port[port_num - sa_dev->start_port];
	agent = port->agent;

	query = kzalloc(sizeof(*query), gfp_mask);
	if (!query)
		return -ENOMEM;

	query->sa_query.port     = port;
	if (rec->rec_type == SA_PATH_REC_TYPE_OPA) {
		status = opa_pr_query_possible(client, device, port_num, rec);
		if (status == PR_NOT_SUPPORTED) {
			ret = -EINVAL;
			goto err1;
		} else if (status == PR_OPA_SUPPORTED) {
			query->sa_query.flags |= IB_SA_QUERY_OPA;
		} else {
			query->conv_pr =
				kmalloc(sizeof(*query->conv_pr), gfp_mask);
			if (!query->conv_pr) {
				ret = -ENOMEM;
				goto err1;
			}
		}
	}

	ret = alloc_mad(&query->sa_query, gfp_mask);
	if (ret)
		goto err2;

	ib_sa_client_get(client);
	query->sa_query.client = client;
	query->callback        = callback;
	query->context         = context;

	mad = query->sa_query.mad_buf->mad;
	init_mad(&query->sa_query, agent);

	query->sa_query.callback = callback ? ib_sa_path_rec_callback : NULL;
	query->sa_query.release  = ib_sa_path_rec_release;
	mad->mad_hdr.method	 = IB_MGMT_METHOD_GET;
	mad->mad_hdr.attr_id	 = cpu_to_be16(IB_SA_ATTR_PATH_REC);
	mad->sa_hdr.comp_mask	 = comp_mask;

	if (query->sa_query.flags & IB_SA_QUERY_OPA) {
		ib_pack(opa_path_rec_table, ARRAY_SIZE(opa_path_rec_table),
			rec, mad->data);
	} else if (query->conv_pr) {
		sa_convert_path_opa_to_ib(query->conv_pr, rec);
		ib_pack(path_rec_table, ARRAY_SIZE(path_rec_table),
			query->conv_pr, mad->data);
	} else {
		ib_pack(path_rec_table, ARRAY_SIZE(path_rec_table),
			rec, mad->data);
	}

	*sa_query = &query->sa_query;

	query->sa_query.flags |= IB_SA_ENABLE_LOCAL_SERVICE;
	query->sa_query.mad_buf->context[1] = (query->conv_pr) ?
						query->conv_pr : rec;

	ret = send_mad(&query->sa_query, timeout_ms, gfp_mask);
	if (ret < 0)
		goto err3;

	return ret;

err3:
	*sa_query = NULL;
	ib_sa_client_put(query->sa_query.client);
	free_mad(&query->sa_query);
err2:
	kfree(query->conv_pr);
err1:
	kfree(query);
	return ret;
}