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
typedef  int /*<<< orphan*/  u16 ;
struct gb_connection {int dummy; } ;
struct gb_bundle {int dummy; } ;

/* Variables and functions */
 unsigned long GB_CONNECTION_FLAG_OFFLOADED ; 
 struct gb_connection* gb_connection_create_flags (struct gb_bundle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 

struct gb_connection *
gb_connection_create_offloaded(struct gb_bundle *bundle, u16 cport_id,
			       unsigned long flags)
{
	flags |= GB_CONNECTION_FLAG_OFFLOADED;

	return gb_connection_create_flags(bundle, cport_id, NULL, flags);
}