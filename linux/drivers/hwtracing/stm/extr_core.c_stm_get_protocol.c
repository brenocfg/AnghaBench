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
struct stm_protocol_driver {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool stm_get_protocol(const struct stm_protocol_driver *pdrv)
{
	return try_module_get(pdrv->owner);
}