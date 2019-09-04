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
struct ipoib_dev_priv {int dummy; } ;
struct ipoib_cm_rx {int /*<<< orphan*/  qp; int /*<<< orphan*/  dev; } ;
struct ib_cm_id {struct ipoib_cm_rx* context; } ;
struct ib_cm_event {int event; } ;

/* Variables and functions */
#define  IB_CM_DREQ_RECEIVED 130 
#define  IB_CM_REJ_RECEIVED 129 
#define  IB_CM_REQ_RECEIVED 128 
 int /*<<< orphan*/  IB_QP_STATE ; 
 int /*<<< orphan*/  ib_modify_qp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_send_cm_drep (struct ib_cm_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_cm_err_attr ; 
 int ipoib_cm_req_handler (struct ib_cm_id*,struct ib_cm_event const*) ; 
 struct ipoib_dev_priv* ipoib_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*) ; 

__attribute__((used)) static int ipoib_cm_rx_handler(struct ib_cm_id *cm_id,
			       const struct ib_cm_event *event)
{
	struct ipoib_cm_rx *p;
	struct ipoib_dev_priv *priv;

	switch (event->event) {
	case IB_CM_REQ_RECEIVED:
		return ipoib_cm_req_handler(cm_id, event);
	case IB_CM_DREQ_RECEIVED:
		ib_send_cm_drep(cm_id, NULL, 0);
		/* Fall through */
	case IB_CM_REJ_RECEIVED:
		p = cm_id->context;
		priv = ipoib_priv(p->dev);
		if (ib_modify_qp(p->qp, &ipoib_cm_err_attr, IB_QP_STATE))
			ipoib_warn(priv, "unable to move qp to error state\n");
		/* Fall through */
	default:
		return 0;
	}
}