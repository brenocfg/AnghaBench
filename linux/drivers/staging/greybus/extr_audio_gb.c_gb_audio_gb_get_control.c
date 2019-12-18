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
typedef  void* u8 ;
struct gb_connection {int dummy; } ;
struct gb_audio_get_control_response {int /*<<< orphan*/  value; } ;
struct gb_audio_get_control_request {void* index; void* control_id; } ;
struct gb_audio_ctl_elem_value {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  GB_AUDIO_TYPE_GET_CONTROL ; 
 int gb_operation_sync (struct gb_connection*,int /*<<< orphan*/ ,struct gb_audio_get_control_request*,int,struct gb_audio_get_control_response*,int) ; 
 int /*<<< orphan*/  memcpy (struct gb_audio_ctl_elem_value*,int /*<<< orphan*/ *,int) ; 

int gb_audio_gb_get_control(struct gb_connection *connection,
			    u8 control_id, u8 index,
			    struct gb_audio_ctl_elem_value *value)
{
	struct gb_audio_get_control_request req;
	struct gb_audio_get_control_response resp;
	int ret;

	req.control_id = control_id;
	req.index = index;

	ret = gb_operation_sync(connection, GB_AUDIO_TYPE_GET_CONTROL,
				&req, sizeof(req), &resp, sizeof(resp));
	if (ret)
		return ret;

	memcpy(value, &resp.value, sizeof(*value));

	return 0;
}