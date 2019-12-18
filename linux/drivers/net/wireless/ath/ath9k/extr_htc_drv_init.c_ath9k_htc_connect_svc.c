#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {void (* tx ) (void*,struct sk_buff*,int,int) ;int /*<<< orphan*/  rx; struct ath9k_htc_priv* priv; } ;
struct htc_service_connreq {TYPE_1__ ep_callbacks; int /*<<< orphan*/  service_id; } ;
struct ath9k_htc_priv {int /*<<< orphan*/  htc; } ;
typedef  enum htc_endpoint_id { ____Placeholder_htc_endpoint_id } htc_endpoint_id ;

/* Variables and functions */
 int /*<<< orphan*/  ath9k_htc_rxep ; 
 int htc_connect_service (int /*<<< orphan*/ ,struct htc_service_connreq*,int*) ; 
 int /*<<< orphan*/  memset (struct htc_service_connreq*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int ath9k_htc_connect_svc(struct ath9k_htc_priv *priv,
					u16 service_id,
					void (*tx) (void *,
						    struct sk_buff *,
						    enum htc_endpoint_id,
						    bool txok),
					enum htc_endpoint_id *ep_id)
{
	struct htc_service_connreq req;

	memset(&req, 0, sizeof(struct htc_service_connreq));

	req.service_id = service_id;
	req.ep_callbacks.priv = priv;
	req.ep_callbacks.rx = ath9k_htc_rxep;
	req.ep_callbacks.tx = tx;

	return htc_connect_service(priv->htc, &req, ep_id);
}