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
typedef  int /*<<< orphan*/  u8 ;
struct gb_operation {int dummy; } ;
struct gb_connection {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 unsigned long GB_OPERATION_FLAG_CORE ; 
 struct gb_operation* gb_operation_create_common (struct gb_connection*,int /*<<< orphan*/ ,size_t,size_t,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_gb_operation_create_core (struct gb_operation*) ; 

struct gb_operation *
gb_operation_create_core(struct gb_connection *connection,
			 u8 type, size_t request_size,
			 size_t response_size, unsigned long flags,
			 gfp_t gfp)
{
	struct gb_operation *operation;

	flags |= GB_OPERATION_FLAG_CORE;

	operation = gb_operation_create_common(connection, type,
					       request_size, response_size,
					       flags, gfp);
	if (operation)
		trace_gb_operation_create_core(operation);

	return operation;
}