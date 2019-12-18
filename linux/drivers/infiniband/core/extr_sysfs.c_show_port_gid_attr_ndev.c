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
struct port_attribute {int dummy; } ;
struct ib_port {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  _show_port_gid_attr (struct ib_port*,struct port_attribute*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_ndev ; 

__attribute__((used)) static ssize_t show_port_gid_attr_ndev(struct ib_port *p,
				       struct port_attribute *attr, char *buf)
{
	return _show_port_gid_attr(p, attr, buf, print_ndev);
}