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
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 TYPE_1__ stm_console ; 
 int stm_source_register_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stm_console_init(void)
{
	return stm_source_register_device(NULL, &stm_console.data);
}