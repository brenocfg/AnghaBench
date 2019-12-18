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
struct avc_command_frame {int dummy; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int LAST_OPERAND ; 
 int /*<<< orphan*/  clear_operands (struct avc_command_frame*,int,int) ; 

__attribute__((used)) static void pad_operands(struct avc_command_frame *c, int from)
{
	int to = ALIGN(from, 4);

	if (from <= to && to <= LAST_OPERAND)
		clear_operands(c, from, to);
}