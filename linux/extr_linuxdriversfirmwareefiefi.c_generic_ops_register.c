#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  get_next_variable; int /*<<< orphan*/  set_variable_nonblocking; int /*<<< orphan*/  set_variable; int /*<<< orphan*/  get_variable; } ;
struct TYPE_4__ {int /*<<< orphan*/  query_variable_store; int /*<<< orphan*/  get_next_variable; int /*<<< orphan*/  set_variable_nonblocking; int /*<<< orphan*/  set_variable; int /*<<< orphan*/  get_variable; } ;

/* Variables and functions */
 TYPE_3__ efi ; 
 int /*<<< orphan*/  efi_kobj ; 
 int /*<<< orphan*/  efi_query_variable_store ; 
 int efivars_register (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_efivars ; 
 TYPE_1__ generic_ops ; 

__attribute__((used)) static int generic_ops_register(void)
{
	generic_ops.get_variable = efi.get_variable;
	generic_ops.set_variable = efi.set_variable;
	generic_ops.set_variable_nonblocking = efi.set_variable_nonblocking;
	generic_ops.get_next_variable = efi.get_next_variable;
	generic_ops.query_variable_store = efi_query_variable_store;

	return efivars_register(&generic_efivars, &generic_ops, efi_kobj);
}