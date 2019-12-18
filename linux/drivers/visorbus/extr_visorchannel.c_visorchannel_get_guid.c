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
struct visorchannel {int /*<<< orphan*/  const guid; } ;
typedef  int /*<<< orphan*/  guid_t ;

/* Variables and functions */

const guid_t *visorchannel_get_guid(struct visorchannel *channel)
{
	return &channel->guid;
}