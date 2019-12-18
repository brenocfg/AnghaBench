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
struct gb_audio_set_control_request {int /*<<< orphan*/  value; void* index; void* control_id; } ;
struct gb_audio_ctl_elem_value {int dummy; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  GB_AUDIO_TYPE_SET_CONTROL ; 
 int gb_operation_sync (struct gb_connection*,int /*<<< orphan*/ ,struct gb_audio_set_control_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct gb_audio_ctl_elem_value*,int) ; 

int gb_audio_gb_set_control(struct gb_connection *connection,
			    u8 control_id, u8 index,
			    struct gb_audio_ctl_elem_value *value)
{
	struct gb_audio_set_control_request req;

	req.control_id = control_id;
	req.index = index;
	memcpy(&req.value, value, sizeof(req.value));

	return gb_operation_sync(connection, GB_AUDIO_TYPE_SET_CONTROL,
				 &req, sizeof(req), NULL, 0);
}