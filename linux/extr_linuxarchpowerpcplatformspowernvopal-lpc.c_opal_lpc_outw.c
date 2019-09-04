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

/* Variables and functions */
 int /*<<< orphan*/  __opal_lpc_outw (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void opal_lpc_outw(u16 val, unsigned long port)
{
	__opal_lpc_outw(cpu_to_le16(val), port);
}