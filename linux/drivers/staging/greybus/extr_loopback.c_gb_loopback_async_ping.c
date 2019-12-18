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
struct gb_loopback {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_LOOPBACK_TYPE_PING ; 
 int gb_loopback_async_operation (struct gb_loopback*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gb_loopback_async_ping(struct gb_loopback *gb)
{
	return gb_loopback_async_operation(gb, GB_LOOPBACK_TYPE_PING,
					   NULL, 0, 0, NULL);
}