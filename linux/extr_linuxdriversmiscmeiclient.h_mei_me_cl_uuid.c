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
typedef  int /*<<< orphan*/  uuid_le ;
struct TYPE_2__ {int /*<<< orphan*/  const protocol_name; } ;
struct mei_me_client {TYPE_1__ props; } ;

/* Variables and functions */

__attribute__((used)) static inline const uuid_le *mei_me_cl_uuid(const struct mei_me_client *me_cl)
{
	return &me_cl->props.protocol_name;
}