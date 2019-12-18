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
struct gb_connection {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_connection_kref_release ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_gb_connection_put (struct gb_connection*) ; 

__attribute__((used)) static void gb_connection_put(struct gb_connection *connection)
{
	trace_gb_connection_put(connection);

	kref_put(&connection->kref, gb_connection_kref_release);
}