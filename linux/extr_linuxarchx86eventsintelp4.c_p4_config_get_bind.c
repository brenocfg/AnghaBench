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
typedef  int /*<<< orphan*/  u64 ;
struct p4_event_bind {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct p4_event_bind*) ; 
 unsigned int p4_config_unpack_event (int /*<<< orphan*/ ) ; 
 struct p4_event_bind* p4_event_bind_map ; 

__attribute__((used)) static struct p4_event_bind *p4_config_get_bind(u64 config)
{
	unsigned int evnt = p4_config_unpack_event(config);
	struct p4_event_bind *bind = NULL;

	if (evnt < ARRAY_SIZE(p4_event_bind_map))
		bind = &p4_event_bind_map[evnt];

	return bind;
}