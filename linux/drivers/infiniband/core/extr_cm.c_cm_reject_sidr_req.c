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
struct ib_cm_sidr_rep_param {int status; } ;
struct cm_id_private {int /*<<< orphan*/  id; } ;
typedef  enum ib_cm_sidr_status { ____Placeholder_ib_cm_sidr_status } ib_cm_sidr_status ;

/* Variables and functions */
 int /*<<< orphan*/  ib_send_cm_sidr_rep (int /*<<< orphan*/ *,struct ib_cm_sidr_rep_param*) ; 
 int /*<<< orphan*/  memset (struct ib_cm_sidr_rep_param*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cm_reject_sidr_req(struct cm_id_private *cm_id_priv,
			       enum ib_cm_sidr_status status)
{
	struct ib_cm_sidr_rep_param param;

	memset(&param, 0, sizeof param);
	param.status = status;
	ib_send_cm_sidr_rep(&cm_id_priv->id, &param);
}