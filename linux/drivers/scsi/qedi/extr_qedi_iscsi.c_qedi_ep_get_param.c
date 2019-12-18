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
struct qedi_endpoint {int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  ip_type; int /*<<< orphan*/  dst_port; } ;
struct iscsi_endpoint {struct qedi_endpoint* dd_data; } ;
typedef  enum iscsi_param { ____Placeholder_iscsi_param } iscsi_param ;

/* Variables and functions */
 int ENOTCONN ; 
#define  ISCSI_PARAM_CONN_ADDRESS 129 
#define  ISCSI_PARAM_CONN_PORT 128 
 int /*<<< orphan*/  TCP_IPV4 ; 
 int sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qedi_ep_get_param(struct iscsi_endpoint *ep,
			     enum iscsi_param param, char *buf)
{
	struct qedi_endpoint *qedi_ep = ep->dd_data;
	int len;

	if (!qedi_ep)
		return -ENOTCONN;

	switch (param) {
	case ISCSI_PARAM_CONN_PORT:
		len = sprintf(buf, "%hu\n", qedi_ep->dst_port);
		break;
	case ISCSI_PARAM_CONN_ADDRESS:
		if (qedi_ep->ip_type == TCP_IPV4)
			len = sprintf(buf, "%pI4\n", qedi_ep->dst_addr);
		else
			len = sprintf(buf, "%pI6\n", qedi_ep->dst_addr);
		break;
	default:
		return -ENOTCONN;
	}

	return len;
}