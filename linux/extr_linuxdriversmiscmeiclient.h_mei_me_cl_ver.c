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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  protocol_version; } ;
struct mei_me_client {TYPE_1__ props; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 mei_me_cl_ver(const struct mei_me_client *me_cl)
{
	return me_cl->props.protocol_version;
}