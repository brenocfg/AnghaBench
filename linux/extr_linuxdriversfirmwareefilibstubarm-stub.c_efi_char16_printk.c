#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct efi_simple_text_output_protocol {int /*<<< orphan*/  (* output_string ) (struct efi_simple_text_output_protocol*,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {scalar_t__ con_out; } ;
typedef  TYPE_1__ efi_system_table_t ;
typedef  int /*<<< orphan*/  efi_char16_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct efi_simple_text_output_protocol*,int /*<<< orphan*/ *) ; 

void efi_char16_printk(efi_system_table_t *sys_table_arg,
			      efi_char16_t *str)
{
	struct efi_simple_text_output_protocol *out;

	out = (struct efi_simple_text_output_protocol *)sys_table_arg->con_out;
	out->output_string(out, str);
}