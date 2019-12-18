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
struct gb_lights_get_lights_response {scalar_t__ lights_count; } ;
struct gb_lights {scalar_t__ lights_count; int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  resp ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GB_LIGHTS_TYPE_GET_LIGHTS ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct gb_lights_get_lights_response*,int) ; 

__attribute__((used)) static int gb_lights_get_count(struct gb_lights *glights)
{
	struct gb_lights_get_lights_response resp;
	int ret;

	ret = gb_operation_sync(glights->connection, GB_LIGHTS_TYPE_GET_LIGHTS,
				NULL, 0, &resp, sizeof(resp));
	if (ret < 0)
		return ret;

	if (!resp.lights_count)
		return -EINVAL;

	glights->lights_count = resp.lights_count;

	return 0;
}