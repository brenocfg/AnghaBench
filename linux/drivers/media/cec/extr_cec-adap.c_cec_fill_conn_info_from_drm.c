#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
struct drm_connector {TYPE_4__ base; TYPE_2__* dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  connector_id; int /*<<< orphan*/  card_no; } ;
struct cec_connector_info {TYPE_3__ drm; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {TYPE_1__* primary; } ;
struct TYPE_5__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_CONNECTOR_TYPE_DRM ; 
 int /*<<< orphan*/  memset (struct cec_connector_info*,int /*<<< orphan*/ ,int) ; 

void cec_fill_conn_info_from_drm(struct cec_connector_info *conn_info,
				 const struct drm_connector *connector)
{
	memset(conn_info, 0, sizeof(*conn_info));
	conn_info->type = CEC_CONNECTOR_TYPE_DRM;
	conn_info->drm.card_no = connector->dev->primary->index;
	conn_info->drm.connector_id = connector->base.id;
}