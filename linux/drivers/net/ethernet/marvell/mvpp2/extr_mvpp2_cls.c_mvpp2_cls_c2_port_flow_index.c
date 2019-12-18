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
struct mvpp2_port {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int MVPP22_CLS_C2_RFS_LOC (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mvpp2_cls_c2_port_flow_index(struct mvpp2_port *port, int loc)
{
	return MVPP22_CLS_C2_RFS_LOC(port->id, loc);
}