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
struct comp_channel {int /*<<< orphan*/  channel_id; int /*<<< orphan*/  iface; } ;
struct TYPE_2__ {int /*<<< orphan*/  cc; } ;

/* Variables and functions */
 scalar_t__ channel_has_mbo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ comp ; 

__attribute__((used)) static inline bool ch_has_mbo(struct comp_channel *c)
{
	return channel_has_mbo(c->iface, c->channel_id, &comp.cc) > 0;
}