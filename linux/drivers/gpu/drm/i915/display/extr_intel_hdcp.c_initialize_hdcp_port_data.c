#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct intel_hdcp_shim {scalar_t__ protocol; } ;
struct hdcp_port_data {int k; TYPE_2__* streams; void* protocol; void* port_type; int /*<<< orphan*/  port; } ;
struct intel_hdcp {int /*<<< orphan*/  content_type; struct hdcp_port_data port_data; } ;
struct intel_connector {TYPE_1__* encoder; struct intel_hdcp hdcp; } ;
struct hdcp2_streamid_type {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  stream_type; scalar_t__ stream_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HDCP_PORT_TYPE_INTEGRATED ; 
 TYPE_2__* kcalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int initialize_hdcp_port_data(struct intel_connector *connector,
					    const struct intel_hdcp_shim *shim)
{
	struct intel_hdcp *hdcp = &connector->hdcp;
	struct hdcp_port_data *data = &hdcp->port_data;

	data->port = connector->encoder->port;
	data->port_type = (u8)HDCP_PORT_TYPE_INTEGRATED;
	data->protocol = (u8)shim->protocol;

	data->k = 1;
	if (!data->streams)
		data->streams = kcalloc(data->k,
					sizeof(struct hdcp2_streamid_type),
					GFP_KERNEL);
	if (!data->streams) {
		DRM_ERROR("Out of Memory\n");
		return -ENOMEM;
	}

	data->streams[0].stream_id = 0;
	data->streams[0].stream_type = hdcp->content_type;

	return 0;
}