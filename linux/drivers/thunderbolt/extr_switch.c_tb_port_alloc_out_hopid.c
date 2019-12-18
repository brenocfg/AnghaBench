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
struct tb_port {int dummy; } ;

/* Variables and functions */
 int tb_port_alloc_hopid (struct tb_port*,int,int,int) ; 

int tb_port_alloc_out_hopid(struct tb_port *port, int min_hopid, int max_hopid)
{
	return tb_port_alloc_hopid(port, false, min_hopid, max_hopid);
}