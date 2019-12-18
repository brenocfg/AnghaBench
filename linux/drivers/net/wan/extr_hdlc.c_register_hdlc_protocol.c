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
struct hdlc_proto {struct hdlc_proto* next; } ;

/* Variables and functions */
 struct hdlc_proto* first_proto ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

void register_hdlc_protocol(struct hdlc_proto *proto)
{
	rtnl_lock();
	proto->next = first_proto;
	first_proto = proto;
	rtnl_unlock();
}