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
struct client_resource {scalar_t__ release; } ;

/* Variables and functions */
 scalar_t__ release_transaction ; 

__attribute__((used)) static int is_outbound_transaction_resource(int id, void *p, void *data)
{
	struct client_resource *resource = p;

	return resource->release == release_transaction;
}